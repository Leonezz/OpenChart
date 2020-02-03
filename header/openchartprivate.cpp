#include "header/openchartprivate.h"
void OpenChartPrivate::coverBackUp()
{
	backup = option.get();
}
void OpenChartPrivate::enableBackUp()
{
	option = backup;
}
void OpenChartPrivate::backStuff(const int error)
{
	switch (error)
	{
	case 1:
		enableBackUp();
	default:
		coverBackUp();
		break;
	}
}