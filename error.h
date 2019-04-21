void fatal_error(char * err_type, char * err_msg) {
	printf("%s: %s\n", err_type, err_msg);
	exit(1);
}

void fatal_error_at_line(char * err_type, char * err_msg, int line) {
	printf("%s: %s\tline: %d\n", err_type, err_msg, line);
	exit(1);

}