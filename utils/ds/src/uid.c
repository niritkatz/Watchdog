/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Uniq ID
 * Reviewer: Anava
 * Last Update: 28/02/2024
 *****************************************/
 #include "uid.h" /*uid_t*/
 #include <unistd.h> /*get_pid*/
 #include <pthread.h> /*mutex*/

static pthread_mutex_t uid_mutex = PTHREAD_MUTEX_INITIALIZER;

const ilrd_uid_t bad_uid = {0, -1, -1};

ilrd_uid_t UIDGenerate(void)
{
	static size_t count = 1;
	ilrd_uid_t uid = {0};

	uid.time = time(NULL);	
	if (uid.time == -1)
	{
		return (bad_uid);
	}
	
	uid.pid = getpid();

	pthread_mutex_lock(&uid_mutex);
	uid.counter = count;
	count++;
	pthread_mutex_unlock(&uid_mutex);

	return (uid);
}

int UIDIsEqual(ilrd_uid_t one, ilrd_uid_t other)
{
	return (one.counter == other.counter && one.pid == other.pid && 0 == difftime(one.time, other.time));
}
