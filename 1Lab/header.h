#ifndef HEADER_H
#define HEADER_H

struct Matrix
{
	int rows;
	int cols;
	double** items;
};

template <class T>
void getSomething(T &x)
{
	cin >> x;
}
