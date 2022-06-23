#include "Lab3_Enclave_t.h"

#include "sgx_trts.h"
#include <string.h>

// Тестовые данные, которые необходимо защитить.
const char data_table[6][41] = {
	"73418125ABC2131EDA72399AB0030DB24BDC5ED3",
	"ABC8915116790BBE31A44CCC9111235478CEDAB0",
	"a03c0a7630b54fd720386e6236e706203ae63195",
	"2f1143d6a4ed8d16c561fd906b3f0f016e4bfbcb",
	"0509b619bdb62392c4d21d5e751d9f81177b0799",
	"3988157b120dfcad3ca094de02baec701c8a1a2c"
};

// Функция поиска значения в тестовых данных.
void table_find(char* buf, size_t len, size_t idx) {
	if (idx < 5) {
		const char* data_ptr = data_ptr = data_table[idx];
		memcpy(buf, data_ptr, strlen(data_ptr + 1));
	}
	else {
		memset(buf, 0, strlen(data_table[0]));
	}
	return;
}