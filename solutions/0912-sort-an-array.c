// This is optimized for arrays with repeated values. Simple quicksort in arrays
// with lots of repeated values will fall to O(n^2). This will hold it under
// O(nlogn) but might end up running slower and consuming more space in average.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swap(int *first_value, int *second_value);
int *partition3(int *array, int left, int right);
void _quicksort(int *array, int array_length, int left, int right);

enum Position { LEFT_MOST, RIGHT_MOST };

int *sortArray(int *nums, int numsSize, int *returnSize) {
  _quicksort(nums, numsSize, 0, numsSize - 1);
  *returnSize = numsSize;
  return nums;
}

void _quicksort(int *array, int array_length, int left, int right) {
  while (left < right) {
    int *middle = partition3(array, left, right);
    if (middle[LEFT_MOST] - left < right - middle[RIGHT_MOST]) {
      _quicksort(array, array_length, left, middle[LEFT_MOST] - 1);
      left = middle[RIGHT_MOST] + 1;
    } else {
      _quicksort(array, array_length, middle[RIGHT_MOST] + 1, right);
      right = middle[LEFT_MOST] - 1;
    }
    free(middle);
  }
}

int *partition3(int *array, int left, int right) {
  int pivot_position = left + (right - left) / 2;
  int pivot = array[pivot_position];
  swap(&array[left], &array[pivot_position]);

  int *middle = (int *)malloc(2 * sizeof(int));

  middle[LEFT_MOST] = left;
  middle[RIGHT_MOST] = left;

  for (int i = left + 1; i <= right; ++i) {
    if (array[i] == pivot) {
      middle[RIGHT_MOST]++;
      swap(&array[middle[RIGHT_MOST]], &array[i]);
    }
    if (array[i] < pivot) {
      middle[LEFT_MOST]++;
      middle[RIGHT_MOST]++;
      swap(&array[middle[RIGHT_MOST]], &array[i]);
      swap(&array[middle[LEFT_MOST]], &array[middle[RIGHT_MOST]]);
    }
  }
  swap(&array[left], &array[middle[LEFT_MOST]]);
  return middle;
}

void swap(int *first_value, int *second_value) {
  int tmp_value = *first_value;
  *first_value = *second_value;
  *second_value = tmp_value;
}
