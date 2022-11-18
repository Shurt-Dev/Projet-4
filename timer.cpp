#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

int main() 
{
	time_t timer;
	time_t tmp;
	time_t alarm;

	struct tm calendar;

	cout << "In how many hours do you want to have a reminder?" << endl;
	cin >> tmp;
	tmp = tmp*3600;
	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	alarm = timer + tmp;
	while (timer != alarm)
	{
		while (timer != time(&tmp))
		{
			char buffer[80];
			time(&timer);
			localtime_s(&calendar, &timer);
			strftime(buffer, 80, "It's %c", &calendar);
			system("CLS");
			cout << buffer << endl;
		}
	}
	
	cout << "Time to feed your baby!!" << endl;

	return 0;
}