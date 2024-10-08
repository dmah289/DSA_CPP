#include<bits/stdc++.h>
using namespace std;

int LomutoPartition(vector<int> &v, int l, int r){
    int pivot = v[r];       // Lấy chốt là phần tử phải cùng
    int i = l-1;            // Giữ vị trí cuối cùng mà nhỏ hơn chốt
    // Duyệt đến trước chốt nếu lớn hơn thì bỏ qua
    // Còn nhỏ hơn thì tăng i lên 1 (phần tử đầu tiên lớn hơn đã bỏ qua)
    // -> Đổi chỗ i, j để dồn phần tử nhỏ hơn về bên phải chốt
    for(int j = l ; j < r ; j++){ 
        if(v[j] <= pivot){
            swap(v[++i], v[j]);
        }
    }
    // Tăng i lên lấy vị trí sau phần tử đầu tiên lớn hơn chốt và swap nó về đuôi
    swap(v[++i], v[r]);
    return i;   // Sau khi swap chốt về vị trí mà các phần tử bên trái nhỏ hơn và bên phải thì lớn hơn 
    // -> Trả về idx chốt để phân hoạch tiếp 2 mảng con left right (không tính pivot vì pivot đã được sắp xếp)
}

int HoarePartition(vector<int> &v, int l, int r){
    // Tìm cặp nghịch thế
    int pivot = v[l];
    int i = l-1, j = r+1;
    while(true){
        // Bắt đầu vòng lặp mới -> Tự dịch 2 con trỏ với do while
        do{
            i++;
        }while(v[i] < pivot);       // Tìm phần tử đầu tiên bên trái >= pivot
        do{
            j--;
        }while(v[j] > pivot);       // Tìm phần tử đầu tiên bên phải <= pivot
        // Việc kiểm tra = pivot để chặn 2 con trỏ không bị TLE
        // Nếu không chặn bằng pivot để  dừng thì có thể sẽ bị lặp vĩnh viễn (cả 2 con trỏ sẽ không gặp được pivot)
        // Còn duyệt được thì đổi chỗ cặp nghịch thế 
        if(i < j)
            swap(v[i], v[j]);
        else return j;      
        // Trả về vị trí chốt nhưng không đảm bảo vị trí chốt này đã được sắp xếp 
        // Vì chỉ đơn giản là phần tử đầu tiên từ bên phải nhỏ hơn thôi mà không phải pivot
    }
}

void QuickSortLomuto(vector<int> &v, int l, int r){
    if(l >= r) return;
    // Lấy idx chốt của mảng đã phân hoạch
    int pivot = LomutoPartition(v, l, r);
    // Phân hoạch tiếp 2 mảng con đã được sắp xếp trước đó
    QuickSortLomuto(v, l, pivot-1);       // [l, pivot)
    QuickSortLomuto(v, pivot+1, r);       // (pivot, r]
}

void QuickSortHoare(vector<int> &v, int l, int r){
    if(l >= r) return;      // Nếu mảng chỉ còn 1 phần tử thì dừng
    // Lấy idx chốt và phân hoạch phần tử nhỏ hơn bên trái, lớn hơn bên phải
    int pivot = HoarePartition(v, l, r);
    // Phân hoạch tiếp 2 mảng đã sắp xếp trước đó
    QuickSortHoare(v, l, pivot);        // [l, pivot]
    QuickSortHoare(v, pivot+1, r);      // [pivot+1, r]
}

int main(){
    int n; cin >> n;
    vector<int> v(n);
    srand(time(NULL));
    for(int i = 0 ; i < n ; i++){
        v[i] = rand() % 100;
    }
    
    QuickSortHoare(v, 0, v.size()-1);

    for(int it : v)
        cout << it << " ";
}