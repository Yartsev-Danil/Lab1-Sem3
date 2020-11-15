#pragma once

#include "Sequence.h"
#include "ArraySequence.h"
#include <ctime>
using namespace std;

template <typename T>
void PrintSeq(Sequence<T>* input) {
	int a = input->GetLength();
	for (int i = 0; i < a; i++) {
		cout << input->Get(i) << " ";
	}
}

template <typename T>
Sequence<T>* Divide1(Sequence<T>* input) {
	int s = input->GetLength();
	Sequence<T>* input1 = new ListSequence<T>(s / 2);
	for (int i = 0; i < s / 2; i++) {
		input1->Set(i, input->Get(i));
	}
	return input1;
}

template <typename T>
Sequence<T>* Divide2(Sequence<T>* input) {
	int s = input->GetLength();
	Sequence<T>* input2 = new ListSequence<T>(s - s / 2);
	for (int i = s / 2; i < s; i++) {
		input2->Set(i - s / 2, input->Get(i));
	}
	return input2;
}

template <class T>
Sequence<T>* Merging(Sequence<T>* input1, Sequence<T>* input2)
{
	int i = 0;
	int j = 0;
	int length1 = input1->GetLength();
	int length2 = input2->GetLength();
	Sequence<T>* input = new ListSequence<T>(length1 + length2);
	while (i + j < length1 + length2) {
		if (i < length1 && j < length2) {
			if (input1->Get(i) < input2->Get(j)) {
				input->Set(i + j, input1->Get(i));
				i++;
			}
			else {
				input->Set(i + j, input2->Get(j));
				j++;
			}
		}
		else if (i == length1) {
			input->Set(i + j, input2->Get(j));
			j++;
		}
		else {
			input->Set(i + j, input1->Get(i));
			i++;
		}
	}
	return input;
}
//слиянием
template<class T>
Sequence<T>* MergeSorter (Sequence<T>* input)
{
	int length = input->GetLength();
		if (length > 1) {
			Sequence<T>* seq1 = Divide1(input);
			Sequence<T>* seq2 = Divide2(input);
			int length1 = seq1->GetLength();
			if (length1 > 1) {
				seq1 = MergeSorter(seq1);
			}
			int length2 = seq2->GetLength();
			if (length2 > 1) {
				seq2 = MergeSorter(seq2);
			}
			input = Merging(seq1, seq2);
		}
	return input;

}



template <typename T>
void Sorting_Time(Sequence<T>* func(Sequence<T>*), Sequence<T>* vec) {
	int start = clock();
	func(vec);
	int finish = clock();
	cout << finish - start << "ms" << endl;
}
//пузырек
template <typename T>
Sequence<T>* Bubble_Sort (Sequence<T>* input)
{
	int s = input->GetLength();
		for (int i = 1; i < s; i++) {
			for (int j = 0; j < i; j++) {
				if (input->Get(i) < input->Get(j)) {
					T a = input->Get(i);
					input->Set(i, input->Get(j));
					input->Set(j, a);
				}
			}
		}
	return input;
	
}
//сортировка выбором от меньшего к большему
template <typename T>
Sequence<T>* Choise_Sort (Sequence<T>* input) {
	int s = input->GetLength();
		for (int i = 0; i < s; i++) {
			int min_ind = i;
			for (int j = i; j < s; j++) {
				if (input->Get(j) < input->Get(min_ind)) {
					min_ind = j;
				}
			}
			T a = input->Get(i);
			input->Set(i, input->Get(min_ind));
			input->Set(min_ind, a);
		}
	return input;
	
}
template<class T>
void compare(Sequence<T>* func1(Sequence<T>*), Sequence<T>* func2(Sequence<T>*), Sequence<T>* seq) {
	int start1 = clock();
	func1(seq);
	int finish1 = clock();
	int result1 = finish1 - start1;
	int start2 = clock();
	func2(seq);
	int finish2 = clock();
	int result2 = finish2 - start2;
	if (result1 < result2)
		cout << "first function is quicker by:" << result2 - result1<<" ms";
	else { cout << "second function is quicker by:" << result1 - result2<< " ms";}
}