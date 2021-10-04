#include<iostream>
#include<vector>
#include<Seqgen.h>
using namespace std;

int main()
{
	Seqgen<double> sequence;
	vector<double> doubleArr;
	vector<double> randomTimeDouble;
	vector<double> risingTimeDouble;
	vector<double> decreasingTimeDouble;
	vector<double> sawToothDouble;
	vector<double> sinTimeDouble;
	vector<double> stepTimeDouble;
	vector<double> quaziOrderedTimeDouble;
	int* time = new int;
	for (int i = 1; i <= 8; i++)
	{
		sequence.risingSequence(&doubleArr, 0, 1000, i * 500000, true, time);
		risingTimeDouble.push_back(*time);
		doubleArr.clear();

		sequence.decreasingSequence(&doubleArr, 0, 1000, i * 500000, true, time);
		decreasingTimeDouble.push_back(*time);
		doubleArr.clear();

		sequence.randomSequence(0, 1000, i * 500000, true, time);
		randomTimeDouble.push_back(*time);
		doubleArr.clear();
		
		sequence.stepOrdered(&doubleArr, 0, 1000, i * 500000, 1000, true, time);
		stepTimeDouble.push_back(*time);
		doubleArr.clear();
		
		sequence.sinSequence(&doubleArr, 0, 1000, i * 500000, 1000, true, time);
		sinTimeDouble.push_back(*time);
		doubleArr.clear();
		
		sequence.sawToothSequence(&doubleArr, 0, 1000, i * 500000, 1000, true, time);
		sawToothDouble.push_back(*time);
		doubleArr.clear();

		sequence.quaziOrdered(&doubleArr, 0, 1000, i * 500000, 1000, true, time);
		quaziOrderedTimeDouble.push_back(*time);
		doubleArr.clear();
	}

	sequence.printArr(&quaziOrderedTimeDouble, quaziOrderedTimeDouble.size());
	/*sequence.Plot(sequence.randomSequence(1000, 100, 1000, true));
	arr.clear();
	
	sequence.risingSequence(&arr, 10, 400, 1000, true);
	sequence.Plot(arr);
	arr.clear();

	sequence.decreasingSequence(&arr, 10, 400, 1000, true);
	sequence.Plot(arr);
	arr.clear();
	
	sequence.sawToothSequence(&arr, 10, 400, 1000, 100, true);
	sequence.Plot(arr);
	arr.clear();

	sequence.sinSequence(&arr, 10, 400, 1000, 100, true);
	sequence.Plot(arr);
	arr.clear();
	
	sequence.stepOrdered(&arr, 10, 400, 1000, 100, true);
	sequence.Plot(arr);
	arr.clear();
	
	sequence.quaziOrdered(&arr, 10, 400, 1000, 100, true);
	sequence.Plot(arr);
	arr.clear();


	cout << endl;

	sequence1.Plot(sequence1.randomSequence(1000, 100, 1000, true));
	arr1.clear();

	sequence1.risingSequence(&arr1, 10, 400, 1000, true);
	sequence1.Plot(arr1);
	arr1.clear();

	sequence1.decreasingSequence(&arr1, 10,400, 1000, true);
	sequence1.Plot(arr1);
	arr1.clear();

	sequence1.sawToothSequence(&arr1, 10, 400, 1000, 100, true);
	sequence1.Plot(arr1);
	arr1.clear();

	sequence1.sinSequence(&arr1, 10, 400, 1000, 100, true);
	sequence1.Plot(arr1);
	arr1.clear();

	sequence1.stepOrdered(&arr1, 10, 400, 1000, 100, true);
	sequence1.Plot(arr1);
	arr1.clear();

	sequence1.quaziOrdered(&arr1, 10, 400, 1000, 100, true);
	sequence1.Plot(arr1);
	arr1.clear();*/


}