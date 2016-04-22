# Sort

> 排序算法

#### Quick Sort

快速排序，通过一趟排序将待排记录分割成两部分，其中一部分中的记录都比另一部分中的记录小，再分别对这两部分进行快排，以达到整个序列有序, 时间复杂度为O(nlog n)。
```c++
int Patition(List& L, int low, int hight)
	// 交换顺序表中字表L[low, hight]的记录，使中枢记录到位，并返回去所在位置；
	// 此时，在该位置之前的记录都比中枢记录小(大)，在其后的记录都比中枢记录大(小)
{
	pivotvalue = L[low];
	pivotkey = L[low];
	while(low < hight)
	{
		while (low < hight && L[hight] >= pivotkey) --hight;
		L[low] = L[hight];
		while (low < hight && L[low] <= pivotkey) ++low;
		L[hight] = L[low];
	}
	L[low] = pivotvalue;
	return low;
}

void QuickSort(List& L, int low, int hight)
{
	if (low < hight)
	{
		pivotloc = Partition(L, Low, hight);
		QuickSort(L, low, pivotloc - 1);
		QuickSort(L, pivotloc + 1, hight);
	}
}
```

#### Heap Sort

