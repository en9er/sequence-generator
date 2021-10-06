#define WITHOUT_NUMPY
#define PI 3.1415
#include<iostream>
#include<chrono>
#include<vector>
#include<cstdlib>
//#include<matplotlibcpp.h>
using namespace std;

template<typename T>
class Seqgen
{
public:
	static_assert(std::is_arithmetic<T>::value, "Template type must be numeric");
	Seqgen() {
		srand(time(NULL));
	};
	void Plot(vector<T> arr);
	void printArr(vector<T>* arr, size_t size);
	
	void risingSequence(vector<T>* arr, int min, int max, int size, bool fix_time = false, int* time = NULL);
	void decreasingSequence(vector<T>* arr, int min, int max, int size, bool fix_time = false, int* time = NULL);
	
	void sawToothSequence(vector<T>* arr, int min, int max, int size, int interval, bool fix_time = false, int* time = NULL);
	void sinSequence(vector<T>* arr, int min, int max, int size, int interval, bool fix_time = false, int* time = NULL);
	void stepOrdered(vector<T>* arr, int min, int max, int size, int interval, bool fix_time = false, int* time = NULL);
	
	void quaziOrdered(vector<T>* arr, int min, int max, int size, int interval, bool fix_time = false, int* time = NULL);

	vector<T> randomSequence(size_t size, int minNum, int maxNum, bool fix_time = false, int* time = NULL);


	bool Swap(vector<T>* arr, int source, int target, double probability = 1);
	double getRandomDouble(double min, double max);
	chrono::microseconds fixTime();

};


template<typename T>
void Seqgen<T>::printArr(vector<T>* arr, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		cout << " " << arr->at(i) << " ";
	}
}

template<typename T>
void Seqgen<T>::risingSequence(vector<T>* arr, int min, int max, int size, bool fix_time, int* time)
{
	chrono::microseconds startTime = fixTime();
	double dmin = min;
	double dmax = max;

	double interval = (dmax - dmin) / (double)size;
	for (int i = 0; i < size; i++)
	{
		arr->push_back(getRandomDouble(dmin, dmin + interval));
		dmin += interval;
	}
	if (fix_time)
	{
		*time = 0;
		chrono::microseconds endTime = fixTime();
		*time = (endTime.count() - startTime.count()) / 1000;
		//cout << "Rising array spent time(" << size << " " <<typeid(T).name() << " elements): " << endTime.count() - startTime.count() << " mcs" << endl;
	}

}

template<typename T>
void Seqgen<T>::decreasingSequence(vector<T>* arr, int min, int max, int size, bool fix_time, int* time)
{
	chrono::microseconds startTime = fixTime();
	double dmin = min;
	double dmax = max;

	double interval = (dmax - dmin) / (double)size;
	for (int i = 0; i < size; i++)
	{
		T tmp = T(getRandomDouble(dmax - interval, dmax));
		arr->push_back(tmp);
		dmax -= interval;
	}
	if (fix_time)
	{
		*time = 0;
		chrono::microseconds endTime = fixTime();
		*time = (endTime.count() - startTime.count()) / 1000;
		//cout << "Decreasing array spent time(" << size << " " << typeid(T).name() << " elements): " << time << " mcs" << endl;
	}
}

template<typename T>
void Seqgen<T>::sawToothSequence(vector<T>* arr, int min, int max, int size, int interval, bool fix_time, int* time)
{
	chrono::microseconds startTime = fixTime();
	int intervalCount = size / interval;
	int i = 0;
	int rise = (interval / 10) * 9;             // 90% of elements is rising part
	int decrease = interval / 10;                // 10% of elements is decreasing sequence
	while (i < intervalCount)
	{
		risingSequence(arr, min, max, rise);
		decreasingSequence(arr, min, max, decrease);
		i++;
	}
	if (fix_time)
	{
		*time = 0;
		chrono::microseconds endTime = fixTime();
		*time = (endTime.count() - startTime.count()) / 1000;		//microseconds / 1000 = milliseconds
		cout << "Sawtooth array spent time(" << size << " " <<typeid(T).name() << " elements): " << endTime.count() - startTime.count() << " mcs" << endl;
	}
}

template<typename T>
void Seqgen<T>::sinSequence(vector<T>* arr, int min, int max, int size, int interval, bool fix_time, int* time)
{
	chrono::microseconds startTime = fixTime();
	int intervalCount = size / interval + int((size % interval) != 0);
	int i = 0;
	while (i < intervalCount)
	{
		int j = i * interval;
		int amplitude = max - min;
		T randMin = 2 * i * PI;             
		T randMax = 2 * (i + 1) * PI;
		T currentStep = (randMax - randMin) / interval;
		while (j < interval * (i + 1) && j < size)
		{
			T randX = T(getRandomDouble(randMin, randMin + currentStep));
			arr->push_back(amplitude / 2 * sin(randX) + amplitude / 2);
			j++;
			randMin += currentStep;
		}
		i++;
	}
	if (fix_time)
	{
		*time = 0;
		chrono::microseconds endTime = fixTime();
		*time = (endTime.count() - startTime.count()) / 1000;        //microseconds / 1000 = milliseconds
		//cout << "Sin sequence array spent time(" << size << " " <<typeid(T).name() << " elements): " << endTime.count() - startTime.count() << " mcs" << endl;
	}
}

template<typename T>
void Seqgen<T>::stepOrdered(vector<T>* arr, int min, int max, int size, int interval, bool fix_time, int* time)
{
	chrono::microseconds startTime = fixTime();
	int i = 0;
	int intervalCount = size / interval + int(size % interval != 0);
	double randMin = min;
	double randMax = max;
	double yInterval = (randMax - randMin) / intervalCount;
	while (i < intervalCount)
	{
		vector<T> tmp = randomSequence((interval / 10) * 8, randMin, randMin + 1);      //80% of interval is horizontal line
		arr->insert(arr->end(), tmp.begin(), tmp.end());
		risingSequence(arr, randMin + 1, randMin + yInterval, (interval / 10) * 2);		//20% of interval is rising line
		randMin += yInterval;
		i++;
	}
	if (fix_time)
	{
		*time = 0;
		chrono::microseconds endTime = fixTime();
		*time = (endTime.count() - startTime.count()) / 1000;        //microseconds / 1000 = milliseconds
		//cout << "Step ordered array spent time(" << size << " " << typeid(T).name() << " elements): " << (endTime.count() - startTime.count()) / 1000 << " ms" << endl;
	}
}

template<typename T>
void Seqgen<T>::quaziOrdered(vector<T>* arr, int min, int max, int size, int interval, bool fix_time, int* time)
{
	chrono::microseconds startTime = fixTime();
	int i = 0;
	int intervalCount = size / interval + int(size % interval != 0);
	T randMin = min;
	T randMax = max;
	T yInterval = (randMax - randMin) / intervalCount;
	while (i < intervalCount)
	{
		risingSequence(arr, randMin, randMin + yInterval, interval);
		randMin += yInterval;
		i++;
	}
	for (int j = 0; j < arr->size() - interval; j++)
	{
		int source = int(getRandomDouble(j, j + interval));
		int target = int(getRandomDouble(j, j + interval));
		Swap(arr, source, target, 0.1);
	}
	if (fix_time)
	{
		*time = 0;
		chrono::microseconds endTime = fixTime();
		*time = (endTime.count() - startTime.count());
		//cout << "Quazi ordered array spent time(" << size << " " << typeid(T).name() << " elements): " << (endTime.count() - startTime.count()) / 1000 << " ms" << endl;
	}
}

template<typename T>
double Seqgen<T>::getRandomDouble(double min, double max)
{
	double tmp = (double)rand() / RAND_MAX;
	return min + tmp * (max - min);
}


template<typename T>
chrono::microseconds Seqgen<T>::fixTime()
{
	return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch());
}


template<typename T>
vector<T> Seqgen<T>::randomSequence(size_t size, int minNum, int maxNum, bool fix_time, int* time)
{
	chrono::microseconds startTime = fixTime();
	vector<T> arr(size);
	for (int i = 0; i < size; i++)
	{
		arr.at(i) = getRandomDouble(minNum, maxNum);
	}
	if (fix_time)
	{
		*time = 0;
		chrono::microseconds endTime = fixTime();
		*time = (endTime.count() - startTime.count()) / 1000;
		//cout << "Random sequence array spent time(" << size << " " <<typeid(T).name() << " elements): " << endTime.count() - startTime.count() << " mcs" << endl;
	}
	return arr;
}

template<typename T>
void Seqgen<T>::Plot(vector<T> arr)
{
	//matplotlibcpp::plot(arr);
	//matplotlibcpp::show();
}

template<typename T>
bool Seqgen<T>::Swap(vector<T>* arr, int source, int target, double probability)
{
	T rand = T(getRandomDouble(0, 1));
	if (rand <= probability)
	{
		T tmp = arr->at(source);
		arr->at(source) = arr->at(target);
		arr->at(target) = tmp;
		return true;
	}
	return false;

}