//
// Created by juango on 12/06/20.
//

#include <iostream>
#include <ctime>

using namespace std;

class MergePointerFunction {
public:
	void MergeSort(int *arr, int begin, int end, bool(*criteria)(int, int)) {
		if (begin < end) {
			int middle = (begin + end) / 2;
			MergeSort(arr, begin, middle, criteria);
			MergeSort(arr, middle + 1, end, criteria);

			int i, j, k;
			int n1 = middle - begin + 1;
			int n2 = end - middle;
			int *L = new int[n1];
			int *R = new int[n2];

			for (i = 0; i < n1; i++)
				L[i] = arr[begin + i];
			for (j = 0; j < n2; j++)
				R[j] = arr[middle + 1 + j];

			i = 0;
			j = 0;
			k = begin;
			while (i < n1 && j < n2) {
				if (arr + i) {
					if (criteria(L[i], R[j])) {//cambiar signo aqui
						arr[k] = L[i];
						i++;
					} else {
						arr[k] = R[j];
						j++;
					}
				}
				k++;
			}
			while (i < n1) {
				arr[k] = L[i];
				i++;
				k++;
			}
			while (j < n2) {
				arr[k] = R[j];
				j++;
				k++;
			}

		}
	}
};

class MergePolymorphism {
public:
	virtual bool criteria(int a, int b) = 0;
};

class PoDownward : public MergePolymorphism {
	bool criteria(int a, int b) {
		return a > b;
	}
};

class MergeWPPolymorphism {
public:
//	virtual bool criteria(int, int) = 0;
	MergePolymorphism *op;

	MergeWPPolymorphism(MergePolymorphism *op1) {
		this->op = op1;
	}

	void MergeSort(int *arr, int begin, int end) {
		if (begin < end) {
			int middle = (begin + end) / 2;
			MergeSort(arr, begin, middle);
			MergeSort(arr, middle + 1, end);

			int i, j, k;
			int n1 = middle - begin + 1;
			int n2 = end - middle;
			int *L = new int[n1];
			int *R = new int[n2];

			for (i = 0; i < n1; i++)
				L[i] = arr[begin + i];
			for (j = 0; j < n2; j++)
				R[j] = arr[middle + 1 + j];

			i = 0;
			j = 0;
			k = begin;
			while (i < n1 && j < n2) {
				if (arr + i) {
					if (op->criteria(L[i], R[j])) {//cambiar signo aqui
//					if (criteria(L[i], R[j])) {//cambiar signo aqui
						arr[k] = L[i];
						i++;
					} else {
						arr[k] = R[j];
						j++;
					}
				}
				k++;
			}
			while (i < n1) {
				arr[k] = L[i];
				i++;
				k++;
			}
			while (j < n2) {
				arr[k] = R[j];
				j++;
				k++;
			}

		}
	}
};

template<class T>
class MergeFunctor {
private:
	T criteria;
public:
	void MergeSort(int *arr, int begin, int end) {
		if (begin < end) {
			int middle = (begin + end) / 2;
			MergeSort(arr, begin, middle);
			MergeSort(arr, middle + 1, end);

			int i, j, k;
			int n1 = middle - begin + 1;
			int n2 = end - middle;
			int *L = new int[n1];
			int *R = new int[n2];

			for (i = 0; i < n1; i++)
				L[i] = arr[begin + i];
			for (j = 0; j < n2; j++)
				R[j] = arr[middle + 1 + j];

			i = 0;
			j = 0;
			k = begin;
			while (i < n1 && j < n2) {
				if (arr + i) {
					if (criteria(L[i], R[j])) {//cambiar signo aqui
						arr[k] = L[i];
						i++;
					} else {
						arr[k] = R[j];
						j++;
					}
				}
				k++;
			}
			while (i < n1) {
				arr[k] = L[i];
				i++;
				k++;
			}
			while (j < n2) {
				arr[k] = R[j];
				j++;
				k++;
			}
		}
	}
};


class FunDownward {
public:
	inline bool operator()(int a, int b) {
		return a > b;
	}
};

bool PFDownward(int a, int b) { return a > b; }


void MergeSort(int *arr, int begin_post, int end_post) {
	if (begin_post < end_post) {
		int middle = (begin_post + end_post) / 2;
		MergeSort(arr, begin_post, middle);
		MergeSort(arr, middle + 1, end_post);

		int i, j, k;
		int n1 = middle - begin_post + 1;
		int n2 = end_post - middle;

		/* create temp arrays */
		int *L = new int[n1];
		int *R = new int[n2];

		/* Copy data to temp arrays L[] and R[] */
		for (i = 0; i < n1; i++)
			L[i] = arr[begin_post + i];
		for (j = 0; j < n2; j++)
			R[j] = arr[middle + 1 + j];

		/* Merge the temp arrays back into arr[l..r]*/
		i = 0; // Initial index of first subarray
		j = 0; // Initial index of second subarray
		k = begin_post; // Initial index of merged subarray
		while (i < n1 && j < n2) {
			if (arr + i) {
				if (L[i] > R[j]) {//cambiar signo aqui
					arr[k] = L[i];
					i++;
				} else {
					arr[k] = R[j];
					j++;
				}
			}
			k++;
		}

		/* Copy the remaining elements of L[], if there
		   are any */
		while (i < n1) {
			arr[k] = L[i];
			i++;
			k++;
		}

		/* Copy the remaining elements of R[], if there
		   are any */
		while (j < n2) {
			arr[k] = R[j];
			j++;
			k++;
		}
	}
}

void FillArray(int *arr, int *arr1, int *arr2, int *arr3, int tam) {
	for (int i = 0; i < tam; i++) {
		int temporal = rand() % 9999;
		*(arr + i) = temporal;
		*(arr1 + i) = temporal;
		*(arr2 + i) = temporal;
		*(arr3 + i) = temporal;
	}
}

//void PrintArray(int *arr, int size) {
//	for (int i = 0; i < size; i++)
//		cout << arr[i] << " ";
//	cout << endl;
//}

int main() {
	int *arr;
	int *arr1;
	int *arr2;
	int *arr3;
	float begin, end, time;
//	int sizes[1] = {1500000};
	int sizes[5] = {25000, 50000, 75000, 100000, 1500000};

	for (int size : sizes) {
		arr = new int[size];
		arr1 = new int[size];
		arr2 = new int[size];
		arr3 = new int[size];

		FillArray(arr, arr1, arr2, arr3, size);

		PoDownward p = *new PoDownward();
		MergeWPPolymorphism z = *new MergeWPPolymorphism(&p);
		MergePointerFunction x;
		MergeFunctor<FunDownward> y{};

		begin = (float) clock();
		z.MergeSort(arr, 0, size);
		end = (float) clock();
		time = end - begin;
		cout << "Polimo " << size << " Tiempo: " << time / CLOCKS_PER_SEC << endl;

		begin = (float) clock();
		x.MergeSort(arr1, 0, size, &PFDownward);
		end = (float) clock();
		time = end - begin;
		cout << "PoiFun " << size << " Tiempo: " << time / CLOCKS_PER_SEC << endl;

		begin = (float) clock();
		y.MergeSort(arr1, 0, size);
		end = (float) clock();
		time = end - begin;
		cout << "Functo " << size << " Tiempo: " << time / CLOCKS_PER_SEC << endl;

		begin = (float) clock();
		MergeSort(arr3, 0, size);
		end = (float) clock();
		time = end - begin;
		cout << "Normal " << size << " Tiempo: " << time / CLOCKS_PER_SEC << endl;

		cout << endl;
	}
	return 0;
}
