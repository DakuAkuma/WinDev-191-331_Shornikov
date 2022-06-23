#include <stdio.h>
#include <tchar.h>
#include <string.h>

/* Специфичные заголовки, для работы с анклавом */
#include "sgx_urts.h"
#include "sgx_tseal.h"
#include "Lab3_Enclave_u.h"
#define ENCLAVE_FILE _T("Lab3_Enclave.signed.dll")

#define BUF_LEN 100 // Размер буфера между анклавом и небезопасным приложением.

//// Тестовые данные, которые необходимо защитить.
//const char data_table[6][41] = {
//	"73418125ABC2131EDA72399AB0030DB24BDC5ED3",
//	"ABC8915116790BBE31A44CCC9111235478CEDAB0",
//	"a03c0a7630b54fd720386e6236e706203ae63195",
//	"2f1143d6a4ed8d16c561fd906b3f0f016e4bfbcb",
//	"0509b619bdb62392c4d21d5e751d9f81177b0799",
//	"3988157b120dfcad3ca094de02baec701c8a1a2c"
//};
//
//// Функция поиска значения в тестовых данных.
//void table_find(char* buf, size_t len, size_t idx) {
//	if (idx < 5) {
//		const char* data_ptr = data_ptr = data_table[idx];
//		memcpy(buf, data_ptr, strlen(data_ptr + 1));
//	}
//	else {
//		memset(buf, 0, strlen(data_table[0]));
//	}
//	return;
//}

// Основная функция.
int main()
{
	char buffer[BUF_LEN] = { 0 };

	/* Активация анклава */
	sgx_enclave_id_t eid;
	sgx_status_t ret = SGX_SUCCESS;
	sgx_launch_token_t token = { 0 };
	int updated = 0;

	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
	if (ret != SGX_SUCCESS) {
		printf("App: error %#x, failed to create enclave.\n", ret);
		return -1;
	}

	/* Работа анклава с данными. */
	while (true) {
		printf("Input index to retrieve or -1 to exit: \t");
		int idx = -1;
		scanf_s("%d", &idx);
		if (idx < 0) {
			return 0;
		}
		table_find(eid, buffer, BUF_LEN, idx); // Поиск по индексу.
		printf("%s\n=================================\n\n", buffer);
	}
	/* Выгрузка анклава. */
	if (sgx_destroy_enclave(eid) != SGX_SUCCESS)
		return -1;

	return 0;
}
