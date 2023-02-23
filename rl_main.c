
#include "prompt/prompt.h"

void test_()
{
	printf("oof");
	signal(SIGQUIT, test_);
}
int	main()
{
	char *tmp;

	while(1)
		
		tmp = get_line();
		signal(SIGINT, NULL);
	free(tmp);
}
