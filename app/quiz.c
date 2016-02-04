/*
 * @Author - Rahul Mahadev
 * Quiz application to demonstrate Secure World execution
 * email - rahul.mahadev7@gmail.com
 */
#include <stdio.h>
#include <string.h>
#include <tee_client_api.h>
#include <ta_quiz.h>
#include <err.h>
int main(void){
 	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	int inp_val;
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
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	
	
	printf("Moving to secure world to start quiz \n");
	//

	printf("Enter the input value:\n");
	scanf("%d",&inp_val);
	printf("Input is %d \n",inp_val );
	op.params[0].value.a = inp_val;
	res = TEEC_InvokeCommand(&sess, TA_QUIZ_CMD_START_QUIZ, &op,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",res, err_origin);
		
	printf("TEE returned value  %d\n", op.params[0].value.a);
	
	printf("Quiz ended\n");
	/* 
	 * Close the session 
	 *
	 */
	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);


 	return 0;
}
