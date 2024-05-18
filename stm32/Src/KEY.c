#include "std_typo.h"
#include "BitMath.h"
#include "DIO/DIO_private.h"
#include "DIO/DIO_INT.h"
#include "KEY.h"
#include <util/delay.h>

static char KEYS[4][4] = {
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'A', '0', '=', '+'}
};

void KEYS_Init(){
	SETPINDIrection(ROW_PORT, ROW_PIN0, PIN_OUTPUT);
	SETPINDIrection(ROW_PORT, ROW_PIN1, PIN_OUTPUT);
	SETPINDIrection(ROW_PORT, ROW_PIN2, PIN_OUTPUT);
	SETPINDIrection(ROW_PORT, ROW_PIN3, PIN_OUTPUT);

	SETPINDIrection(COL_PORT, COL_PIN0, PIN_INPUT);
	SETPINDIrection(COL_PORT, COL_PIN1, PIN_INPUT);
	SETPINDIrection(COL_PORT, COL_PIN2, PIN_INPUT);
	SETPINDIrection(COL_PORT, COL_PIN3, PIN_INPUT);



	setpinvalue(ROW_PORT, ROW_PIN0, HIGH);
	setpinvalue(ROW_PORT, ROW_PIN1, HIGH);
	setpinvalue(ROW_PORT, ROW_PIN2, HIGH);
	setpinvalue(ROW_PORT, ROW_PIN3, HIGH);
}

ERROR_status check_overflow(uint8 *val){
	uint8 max_val[] = {4,2,9,4,9,6,7,2,9,5}, eq = 0, les = 0;
	ERROR_status er = E_OK;
	for(uint8 i = 0; i < 10; i++){
		if(val[i] > max_val[i] && !les){
			er = E_NOK;
			break;
		}
		if(val[i] > max_val[i] && eq){
			er = E_NOK;
			break;
		}
		if(val[i] == max_val[i] && !les){
			eq = 1;
		}
		if(val[i] < max_val[i]){
			les = 1;
			break;
		}
	}
	return er;
}

ERROR_status get_int(uint8 *val, u32 *ans){
	ERROR_status er = E_OK;

	u32 base = 1;
	uint8 i = 9;
	while(val[i] == '$') i--;

	if(i == 9){
		er = check_overflow(val);
	}

	if(er == E_OK){
		for(; i >= 0; i--){
			*ans += ((u32)val[i] * base);
			base *= 10;
			if(i == 0) break;
		}
	}
	return er;
}

void reverse(uint8 *res, uint8 len){
	for(uint8 i = 0; i < len / 2; i++){
		uint8 temp = res[i];
		res[i] = res[len - 1 - i];
		res[len - 1 - i] = temp;
	}
}

void init_arr(uint8 *arr, uint8 len){
	for(uint8 i = 0; i < len; i++){
		arr[i] = '$';
	}
}

ERROR_status get_char(u32 val, uint8 *res, uint8 *res_len, uint8 sign){
	ERROR_status er = E_OK;
	uint8 i = 0;
	while(val){
		res[i++] = (uint8)(val % 10) + '0';
		val /= 10;
	}
	if(sign){
		res[i++] = '-';
		res[i++] = ' ';
	}
	*res_len = i;
	reverse(res, *res_len);
	return er;
}

ERROR_status get_ans(uint8 *fnum, uint8 *snum, uint8 op, u32 *ans, uint8 *sign){
	ERROR_status er = E_OK;

	u32 fint = 0, sint = 0;
	ERROR_status er1 = get_int(fnum, &fint);
	ERROR_status er2 = get_int(snum, &sint);

	if(er1 == E_NOK || er2 == E_NOK) return E_NOK;

	switch(op){
	case '+':
		*ans = fint + sint;
		break;
	case '-':
		if(fint < sint){
			*sign = 1;
			*ans = sint - fint;
		}
		else *ans = fint - sint;
		break;
	case '*':
		*ans = fint * sint;
		break;
	case '/':
		*ans = fint / sint;
		break;
		default: er = E_NOK;
	}

	return er;
}

ERROR_status CALC(uint8 *input, uint8 in_len, uint8 *res, uint8 *res_len){
	ERROR_status valid = E_OK;
	uint8 fnum[10], snum[10], op = 'q';
	init_arr(fnum, 10);
	init_arr(snum, 10);
	uint8 first = 1, second = 0, ind_f = 0, ind_s = 0;
	for(uint8 i = 0; i < in_len - 1; i++){
		if((input[i] - '0') >= 0 && (input[i] - '0') < 10 && first){
			if(ind_f == 10){
				valid = E_NOK;
				break;
			}
			fnum[ind_f++] = (input[i] - '0');
		}
		else if((input[i] - '0') >= 0 && (input[i] - '0') < 10 && second){
			if(ind_s == 10){
				valid = E_NOK;
				break;
			}
			snum[ind_s++] = (input[i] - '0');
		}
		else{
			if(op != 'q'){
				valid = E_NOK;
				break;
			}
			op = input[i];
			second = 1;
			first = 0;
		}
	}

	if(ind_s == 0 || ind_f == 0){
		valid = E_NOK;
	}
	u32 ans = 0;
	uint8 sign = 0;
	if(valid) valid = get_ans(fnum, snum, op, &ans, &sign);
	if(valid) valid = get_char(ans, res, res_len, sign);
	return valid;


}

uint8 Get_value(uint8 *value){
	uint8 rowind = 0, colind = 0, f = 0;
	ROWS R[4] = {ROW_PIN0, ROW_PIN1, ROW_PIN2, ROW_PIN3};
	COLS C[4] = {COL_PIN0, COL_PIN1, COL_PIN2, COL_PIN3};

	for(uint8 i = 0; i < 4; i++){
		*value = 'q';
		setpinvalue(ROW_PORT, R[i], LOW);
		for(uint8 j = 0; j < 4; j++){
			uint8 ret = 1;
			getpinvalue(COL_PORT, C[j], &ret);
			if(ret == 0){
				_delay_ms(2);
				while(ret == 0){
					rowind = i;
					colind = j;
					f = 1;
					getpinvalue(COL_PORT, C[j], &ret);
				}
			}
			if(f) break;
		}
		setpinvalue(ROW_PORT, R[i], HIGH);
		if(f) break;
	}
	if(f){
		*value = KEYS[rowind][colind];
		return 'Y';
	}

	else return 'N';
}
