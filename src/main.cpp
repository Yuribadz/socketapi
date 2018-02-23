#include <thread>
#include <iostream>
#include <thread>
#include <stdint.h>
#include <stdio.h>
void hello(){
    std::cout << "Hello from thread " << std::endl;
}

typedef enum {
	/**
	* The function call executed successfully.
	*/
	MafOk = 0,
	/**
	* <p>The function could not provide any service at this point in time.
	* The problem that occurred is temporary, and the caller may retry later.
	*
	* <p>Note that this error code is only to be returned from interfaces
	* that explicitly declares that this error code can be returned
	* and have this meaning. Currently all use cases of MAF SPIs interprets
	* anything other than MafOk
	* a failure and will abort the operation.</p>
	*/
	MafTryAgain = 1,
	/**
	* <p>The function could not provide any service since the service is not started.</p>
	*/
	MafNotActive = 2,
	/**
	* <p>The function call failed, an error has occurred which is specific
	* for the function implementation.</p>
	*/
	MafFailure = -1,
	/**
	* <p>The function call failed since something sought after did not exist.
	* Detailed information can be obtained from MafMgmtSpiThreadContext.</p>
	*/
	MafNotExist = -2,
	/**
	* <p>The function call failed since something that was to be created already exists.
	* Detailed information can be obtained from MafMgmtSpiThreadContext.</p>
	*/
	MafAlreadyExist = -3,
	/**
	* <p>The function call failed and was aborted. The function did not change
	* any persistent data.
	* Detailed information can be obtained from MafMgmtSpiThreadContext.</p>
	*/
	MafAborted = -4,
	/**
	* <p>The function call failed since an object is locked.</p>
	*/
	MafObjectLocked = -5,
	/**
	* <p>The function call failed in the prepare phase of the transaction.
	* The transaction has been aborted.</p>
	*/
	MafPrepareFailed = -6,
	/**
	* <p>The function call failed in the commit phase.
	* Some participants may have failed to commit and the
	* total transactional result may be inconsistent. A human
	* may be needed to resolve the situation.</p>
	*/
	MafCommitFailed = -7,
	/**
	* <p>The function call failed since an argument is invalid.</p>
	*/
	MafInvalidArgument = -8,
	/**
	* <p>The function call failed since the data did not validate.
	* The only time this error code should be used is as return
	* code from the commit operation</p>
	*/
	MafValidationFailed = -9,
	/**
	* <p>The function call failed since there was no available resource, such as memory.</p>
	*/
	MafNoResources = -10,
	/**
	* <p>Some vital resource needed in the function call has timed out.
	* It is unspecified whether the call succeeded or whether it did not,
	* the user of interface must find it out.</p>
	*/
	MafTimeOut = -11
} MafReturnT;

int main(){
	
	printf ("Characters: %d", MafTimeOut);
	return 0;
}