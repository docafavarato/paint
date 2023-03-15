#include "paint.h"

int main()
{
	Paint paint;

	while (paint.running())
	{
		paint.update();
		paint.render();
	}

	return 0;
}