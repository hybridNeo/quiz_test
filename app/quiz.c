/*
 * @Author - Rahul Mahadev
 * Quiz application to demonstrate Secure World execution
 * email - rahul.mahadev7@gmail.com
 */
#include <stdio.h>
#include <string.h>
#include <tee_client_api.h>
#include <tee_api_defines.h>
#include <tee_api_types.h>
#include <ta_quiz.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
int main(void){
 	uint8_t question[32] =  {0};
 	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_Operation op;
	TEEC_UUID uuid = TA_QUIZ_UUID;
	uint32_t err_origin;
	res = TEEC_InitializeContext(NULL, &ctx); // This basically checks if a TEE is present in the system
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);   
	/*
	 * Open a session to the  TA
	 */
	res = TEEC_OpenSession(&ctx, &sess, &uuid,TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",res, err_origin);


	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */

	memset(&op, 0, sizeof(op));
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_MEMREF_TEMP_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[1].tmpref.buffer = question;
	op.params[1].tmpref.size  = sizeof(question);
	printf("Before:%d \n",question[0] );
	printf("********************** QUIZ **************************\n");
	while(1){
		res = TEEC_InvokeCommand(&sess, TA_QUIZ_CMD_START_QUIZ, &op,&err_origin);
		if (res != TEEC_SUCCESS)
			errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",res, err_origin);	
		printf("TEE returned value  %d\n", op.params[0].value.a);
		if(op.params[0].value.a == 0){
			break;
		}else{
			printf("After: %d \n",question[0] );
		}
		
	}	
	printf("Quiz ended\n");
	/* 
	 * Close the session 
	 */
	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);


 	return 0;
}
