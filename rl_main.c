
#include "prompt/prompt.h"

int	main()
{
	char *tmp;

	while(1)
		tmp = prompt();
	free(tmp);
}
