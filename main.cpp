#include <iostream>
#include <stdlib.h>
#include<sqlite3\sqlite3.h>

int main()
{
	sqlite3 *handle = NULL;/* SQLite database is represented by a pointer to an instance of the structure named "sqlite3"  */
	sqlite3_stmt*statement_handle;// statement handle
	char databaseFile[] = { "test.db" }; //  Name of the Database File in the file system
	char query[] = { "SELECT * FROM first" };
	//SQLite database file is opened/created(if the file doesn’t exist) in the filesystem and a database connection handle is assigned to it.
	if (sqlite3_open(databaseFile, &handle) == SQLITE_OK)  //  open an SQLite database file
	{
		printf("Successfully Connected\n");
	}
	else
	{
		printf("Not Connected\n");// closing database connection
	}
	// Creating a statement handle for the query
	/*
	To execute an SQL query, it must first be compiled into a byte-code program using one of  sqlite3_prepare_*() family of routines.
	This compiled prepared statement is referenced by the statement_handle.
	On success, the sqlite3_prepare() family of routines return SQLITE_OK; otherwise an error code is returned.
	*/
	if (sqlite3_prepare(handle, query, strlen(query), &statement_handle, NULL) != SQLITE_OK)
	{
		printf("unable to execute sqlite3_prepare()\n");
	}
	/*
	This compiled prepared statement can be executed by the sqlite3_step() routine
	*/
	int row = 0;
	while (sqlite3_step(statement_handle) != SQLITE_DONE)     // Executing query reference d by statement handle
	{
		int bytes;
		const unsigned char*text;
		bytes = sqlite3_column_bytes(statement_handle,0);
		text = sqlite3_column_text(statement_handle, 1);
		int noc = sqlite3_data_count(statement_handle);// number of columns
		printf("%d: %s\n", row, text);
		row++;

	}
	//The sqlite3_finalize() function is called to delete a prepared statement.
	sqlite3_finalize(statement_handle);      //destroying statement handle
	sqlite3_close(handle);
	printf("Successfully Closed\n");
	return 0;
}