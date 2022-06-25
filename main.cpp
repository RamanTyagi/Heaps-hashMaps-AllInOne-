//
//  main.cpp
//  HashMaps
//
//  Created by RAMAN TYAGI on 25/08/21.
//  Copyright © 2021 RAMAN TYAGI. All rights reserved.
//
//VECTORS ARE NOT PASSED WITH REFERENCE LIKE ARRAYS
// JIS FUNCTION MEIN ISS USE KR RHE HO ESE KRO
// -> vector<int> &arr;
/*
 ~~~~~~~~~~~~~~~~~~~THEORY: HASH MAPS~~~~~~~~~~~~~~~~~~~~~~
 ##########################################################
 IMPLEMENTATION :
 ->unordered_map<int,int> uq
 ->unordered_map<int,int> :: iterator it;
 ->uq.find(temp)!=uq.end() *iska mtlb hai mil gya!*
###########################################################
 
 ->unordered_map is an associated container that stores elements formed by the combination of key-value and a mapped value.
 ->The cost of search,insert and delete from hashtable is on avg O(1).
 ->map(like set) is an ordered sequence of unique keys whereas unordered_map keys can be stored in any order!
 ->The map is implemented as a balanced tree structure that is why it is possible to maintain order between between the elements.
 map : Tc is O(logn).
 unordered_map : Tc is O(1).
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 ~~~~~~~~~~~~~~~~~THEORY PRIORITY QUEUE~~~~~~~~~~~~~~~~~~~~
 ##########################################################
  IMPLEMENTATION :
  ->priority_queue<int> p;(MAX HEAP)
  ->priority_queue<int,vector<int> greater<int>> p;(MIN HEAP)
  ->Sare stack wale operations chlte h pop,push,top wale!
###########################################################
 -->Priority queues are a type of container adapters , specifically designed such that first element of the queue is the greatest of all elements in the queue and elements are in non inc. order!
 ->Jo top() hai vo chlta hai O(1) mein!
 ->Baaki push() , pop() chlte hai O(logn) mein!
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 */
#include <iostream>
#include<unordered_map>
#include<vector>
#include<queue>
using namespace std;
/*
 Har ek element ko uski frequency ke sath store kra lia
 --> Fir jis element ki frequency sbse zyda hai use nikalte gye or akhiri mein return kradia!!
 */
char maxFrequency(string str)
{
    char reschar = '\0';
       unordered_map<char,int> ump;
       int i;
       for(i=0;str[i]!='\0';i++)
       {
           ump[str[i]]++;
       }
       int c=INT_MIN;
       for(i=0;str[i]!='\0';i++)
       {
           if(ump[str[i]]>c)
           {
               c=ump[str[i]];
               reschar=str[i];
           }
       }
    return reschar;
}
/*
 ->Ek hashmap bnaya usme sare elements arr1 ke daldie unki frequencies ke sath !
 ->fir arr2 mein loop lga kr check kia ki kya vo element ek baar bhi aa rha h !
 -> If yes freq ko 0 krke , element print krdo!!!
 */
void getCommonElement1(int arr1[],int a,int arr2[],int b)
{
    unordered_map<int, int> mp;
    int i;
    for(i=0;i<a;i++)
    {
        mp[arr1[i]]++;
    }
    for(i=0;i<b;i++)
    {
        if(mp[arr2[i]]>0)
        {
            cout<<arr2[i]<<" ";
            mp[arr2[i]]=0;
        }
    }
}
/*
 ->Ek hashmap bnaya usme arr2 ki sare elements apni apni frequencies ke sath daldiye!
 ->fir loop lgaya arr1 or check kia kya arr1 ke ksi particular element ki frequency zero se bdi h , agr hai to us element ko print krke uski frequency ko map mein 1 se km krdia!
 */
void getCommonElement2(int arr1[],int a,int arr2[],int b)
{
    unordered_map<int, int> mp;
    int i;
    for(i=0;i<b;i++)
    {
        mp[arr2[i]]++;
    }
    for(i=0;i<a;i++)
    {
        if(mp[arr1[i]]>0)
        {
            cout<<arr1[i]<<" ";
            mp[arr1[i]]--;
        }
    }
}
/*
 ************************VIMP******************************
 Approach:
 STEP1:Array pe loop chlakr sbki value true krli!
 STEP2:Ab ek or loop chlaya array pe , agr current element se ek chota element bhi hai array mein to is current element ki value ko false krdo!
 STEP3:Ek or loop chlaya array pe , agr true hai value to use ek vector mein push krlia -> ab is value se bdi values dhundi jo iske sequence mein h or unhe bhi vector mein push krte gye!
 STEP4:Agr is vector ka sum purane sbse zyda wale ke size se bda h to is vector ko ek ans vale vector mein dal dia bs end mein is ans vector ku return krdi!!!
 
 
~~~~length And starting bhi use krke print kra skte h~~~~~
 **************Space complexity ght jaegi!!****************
 ************************VIMP******************************
 */
vector<int> longestConsecutiveSequence(int arr3[],int n)
{
    vector<int> ans;
    int vec_Size=INT_MIN;
    unordered_map<int, bool> mp;
    int i;
    for(i=0;i<n;i++)
    {
        mp[arr3[i]]=true;
    }
    for(i=0;i<n;i++)
    {
        if(mp.find(arr3[i]-1)!=mp.end())
        {
            mp[arr3[i]]=false;
        }
    }
    for(i=0;i<n;i++)
    {
        if(mp[arr3[i]]==true)
        {
            vector<int> res;
            res.push_back(arr3[i]);
           // cout<<arr3[i]<<"\n";
            int temp=arr3[i]+1;
            while(mp.find(temp)!=mp.end())
            {
                //cout<<temp<<"\n";
                res.push_back(temp);
                temp=temp+1;
            }
            /*for(int k=0;k<res.size();k++)
                cout<<res[k]<<"\n";*/
            int m=res.size();
            if(m>vec_Size)
                {
                       ans=res;
                       vec_Size=m;
                    /*for(int k=0;k<ans.size();k++)
                                   cout<<ans[k]<<"\n";*/
                }
        }
       
    }
    return ans;
}
/*
 Time : O(nlogk) -> n elements ko k ki priority queue mein dalna hai!
 Space: O(k)  -> priority queue ka size!
 #
 Approach :
 -> Sbse bekar player priority queue ke top pe hoga ab array pe traverse krna shuru kra .
 -> Agr array ke agle indexes pe jo players hai vo ache hai top wale se to , priority queue mein se pop krdo bekar player ko & ache player ko push krlo!
 */
void kLargestElements(int arr[],int n,int k)
{
    priority_queue<int,vector<int>,greater<int>> p;
    for(int i=0;i<n;i++)
    {
        if(i<k)
        p.push(arr[i]);
        else
        {
            if(arr[i]>p.top())
            {
                p.pop();
                p.push(arr[i]);
            }
        }
    }
    while(p.size()>0)
    {
        cout<<p.top()<<" ";
        p.pop();
    }
    
}
/*
 #
 Time : O(nlogk) -> n elements ko k ki priority queue mein dalna hai!
 Space: O(k)  -> priority queue ka size!
 #
 Approach:
 ->Acquire and release strategy!
 ->Phle to shuru ke k elements priority queue mein dal die!
 ->Hme pta h jb maximum differ k index se kr skte hai elements to sbse chota element phle k mein mil jaega!
 ->Ab k se array ke size tk loop chlaenge!
 ->sbse chote element ko print&remove krte jaenge!
 ->next element ko dalte jaenge!
 */
void sortKSorted(int arr[],int n,int k)
{
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=0;i<=k;i++)
    {
        pq.push(arr[i]);
    }
    for(int i=k+1;i<n;i++)
    {
        cout<<pq.top()<<" ";
        pq.pop();
        pq.push(arr[i]);
    }
    while(pq.size()>0)
    {
        cout<<pq.top()<<" ";
        pq.pop();
    }
}
int size(priority_queue<int>left,priority_queue<int>right)
{
    int p=left.size();
    int q=right.size();
    return p+q;
}
/*
 **********************VIMP********************************
 Work to achieve:
 1.peek -> median ko dikhao!
 2.remove -> median ko remove kro!
 #INTUITION:
 -->Do priority queue bnaenge left and right!
 --> left will be max heap!
 --> right will be min heap!
 -->left will contain smaller half of data
 -->right will contain greater half of data
 ~~~~> left and right ke size mein maximum difference 1 ka aa skta hai!
 #APPROACH:
 -->Agr right ka size >0 hai & left ke top se bda element aa rha hai to right mein push kro!
 -->If not left mein push kro!
 -->Jb bhi size mein 2 ka difference aajae zyda size wale se element km size wale mein daldo!
**********************VIMP********************************
 */
int peekMp(priority_queue<int>left,priority_queue<int,vector<int>,greater<int>>right)
{
    if(left.size()>=right.size())
    {
        int x=left.top();
        return x;
    }
    else
    {
        return right.top();
    }
}
int removeMp(priority_queue<int>&left,priority_queue<int,vector<int>,greater<int>>&right)
{
    if(left.size()>=right.size())
    {
        int x=left.top();
        left.pop();
        return x;
    }
    else
    {
        int y = right.top();
        right.pop();
        return y;
    }
}
void addToMp(priority_queue<int> &left,priority_queue<int,vector<int>,greater<int>> &right,int value)
{
    if(right.size()>0&&value>right.top())
    {
        right.push(value);
    }
    else
    {
        left.push(value);
    }
    if(left.size()-right.size()==2)
    {
        right.push(left.top());
        left.pop();
    }else if(right.size()-left.size()==2)
    {
        left.push(right.top());
        right.pop();
    }
}
class li_Pair
{
public:
    int li;//list index
    int di;//data index
    int val;
};
/*
-> priority_queue<li_Pair,vector<li_Pair>,compareValue>;
 -> WHEN WE USE PRIORITY QUEUE WITH CLASS/STRUCTURE THEN WE NEED THIS KIND OF SYNTAX WHERE COMPAREVALUE IS THE FUNCTOR OR COMPARISON FUNCTION!
 *******************VIMP***********************************
 HOW PRIORITY QUEUE WILL DECIDE KI KONSA PAIR SBSE CHOTA HAI?
 SOL:
 #opearator return true krega jb next object ki value choti hogi!
 -->min heap bnaega value ke hisab se
 */
class compareValue
{
public:
    bool operator()(li_Pair const& li1,li_Pair const& li2)
    {
        return li1.val>li2.val;
    }
};
/*
********************VIMP***********************************
 APPROACH:
 ->Sbse phle sari lists ke phle index wali value se ek min priority queue bnayi!
 ->list index(li) ko i ke equal rkha , data index(di) ko zero rkha
 -> Ab jb tk priority queue ka size zero se bda rhta hai , hr pair ko pop krate jao unka di bdhao -> li ke size se km hai ye check kro
 -> ki khi vo list khtm to ni hogyi ??
 -> Agr nhi hui to agle element ko value mein set krke priority queue mein push krte jao!
********************VIMP***********************************
 */
vector<int> mergeKSortedLists(vector<vector<int>> lists)
{
    int n = lists.size();
    vector<int> rv;
    priority_queue<li_Pair,vector<li_Pair>,compareValue> pq;
    for(int i=0;i<n;i++)
    {
        li_Pair tp;
        tp.li=i;
        tp.di=0;
        tp.val=lists[i][0];
        pq.push(tp);
    }
    while(pq.size()>0)
    {
        li_Pair p=pq.top();
        pq.pop();
        rv.push_back(p.val);
        p.di++;
        if(p.di<lists[p.li].size())
        {
            p.val=lists[p.li][p.di];
            pq.push(p);
        }
    }
    
    return rv;
}
/*
 ****************MAKING OUR OWN PRIORITY : MAX HEAP***********
 
-> Array ki list ko complete binary tree ki trh visualize krenge!
-> Functions perform array pe hi krenge !
->Pr visualize krenge complete binary tree ki trh
 Requirements ::
 #Heap order property(HOP) -> Ye help krege peek ko O(1) mein dene ke liye!
 #Complete Binary tree(CBT) -> Array list pe indexo ka rule follow hojaea -> Jiski vjh se upHeapify ya downHeapify lga paenge O(logn) mein nhi to fir preorder , postorder vgrh se krna pdega to O(n) mein le jaenge!
 ****************MAKING OUR OWN PRIORITY : MAX HEAP***********
 */

/*
  *****************TIME COMPLEXITY:{O(log(n))}***************
 --> Kyuki sirf height pe depend krega!
Approach:
 1. Nye element ko last index pe dal dia!
 2. Uska index upHeapify ko bhej dia
 3. Parent index nikal kr check kiya ki:
  -> Kya child index wala element bda hai parent index wale element se?(child wale ki priority zyda to nii h?)
 -> Agr hai to swap krdo!
 Or ye chlate rho jb tk root tk naa chl jae!
 */
void upHeapify(vector<int> &arr,int ele_ind)
{
    int par_index=(ele_ind-1)/2;
    if(par_index>=0&&arr[ele_ind]>arr[par_index])
    {
        swap(arr[ele_ind], arr[par_index]);
        upHeapify(arr, par_index);
    }
}
/*
 **********************VIMP***********************************
 *****************TIME COMPLEXITY:{O(nlog(n))}***************
 #############################################################
 -> n elements ko dalenge upHeapify(Ologn) se
->Akhiri wale level ke liye chlega height ke times
 # n/2 * h chelga iska lie (O(nlogn))
 # n/4 * h-1 chelga iske upr wale level ke lie
 and so on...........
 ->Hr element se upheap lga do!
 -> sbse upr wale element ke lie sbse km kaam!
-> ZYDA ELEMENTS KE LIYE ZYDA KAAM HOGA IS CASE MEIN!
 #############################################################
Approach:
1.Phle wala element to max heap m phle se hi h --> ek element hi h array mein to vo heap m bhi h!
2. i = 1 se traverse krna shuru kro or upHeapify call krte jao us index i ke sath!
 
 */

void CreateMaxHeap(vector<int> &arr)
{
    int i;
    int n=arr.size(); // Current size of the vector aajaega!
    for(i=1;i<n;i++)
    {
        upHeapify(arr,i);
    }
}
/*
*****************TIME COMPLEXITY:{O(nlog(n))}***************
  -> n elements ko dalenge upHeapify(Ologn) se
 Approach:
 1.Element jo nya dalna hai use array mein akhiri mein add krdia!
 2. Ab last ka index dekr upHeapify chla do!
 */
void AddToMaxHeap(vector<int> &arr,int ele)
{
    int i = arr.size(); // current size aajaega -> akhiri index , jahan heapify lgega!
    arr.push_back(ele);
    upHeapify(arr, i);
}
/*
*****************TIME COMPLEXITY:(O(1))***********************
 -> zeroth index wala return krna h bs!
 Approach:
 ->Jo zeroth index pe hoga uski hi maximum priority hogi!
 ->Bs is element ko return krdo!
 */
int peekToMaxHeap(vector<int> arr)
{
    int n=arr.size();
    if(n==0)
    {
        cout<<"UNDERFLOW!!!!";
        return -1;
    }
    return arr[0];
}
/*
*****************TIME COMPLEXITY:{O(log(n))}***************
  --> Kyuki sirf height pe depend krega!
 ->Jo index (0) bheja hai use largest element ka index man lia (Acc to max heap)
 ->fir uska left index and right index nikala
 ->Ab left and right mein jo bda hai us element se swap krdia
 ->dobara khud ko call krlia largest wale index ke sath
 */
void downHeapify(vector<int> &arr,int i)
{
    int n = arr.size();
    int largest=i;
    int left=(2*i)+1;
    int right=(2*i)+2;
    if(left<n&&arr[left]>arr[i])
    {
        largest=left;
    }
    if(right<n&&arr[right]>arr[i]&&arr[right]>arr[left])
    {
        largest=right;
    }
    if(i!=largest)
    {
        swap(arr[i],arr[largest]);
        downHeapify(arr, largest);
    }
}
/*
 *****************TIME COMPLEXITY:{O(nlog(n))}***************
 -> n elements ko remove krege downHeapify(Ologn) se
 Approach:
 ->First Index or last Index wale elements ko swap kia!
 ->Us first index wale element ko alg se temp mein store kra lia , kyuki isi maximum priority wale element ko return krna hai!
 ->Ab downHeapify call kria zeroth index ke sath!
 ->Vo dobara se heap bna dega , element ko remove krne ke baad bhi
 */
int RemoveFromMaxHeap(vector<int> &arr)
{
    int n = arr.size();
    int temp=arr[0];
    arr[0]=arr[n-1];
    arr[n-1]=0;
    downHeapify(arr,0);
    return temp;
}
/*
 **********************VIMP***********************************
 *****************TIME COMPLEXITY:{O(n)}**********************
 #############################################################
 ->Akhiri wale level ke liye chlega hi ni islie time complexity km hogi createMaxHeap wale se!
 ->Hr element se downheap lga do!
 -> sbse upr wale element ke lie sbse zyda kaam (logn) ka
  -> ZYDA ELEMENTS KE LIYE KM HOGA IS CASE MEIN !
 #############################################################
 Approach:
 1.n/2 se call lgani shuru krenge down heapify ko!
 */
void BuildMaxHeap(vector<int> &arr)
{
    int n =arr.size();
    for(int i=n/2;i>=0;i--)
    {
        downHeapify(arr, i);
    }
}
/*
 *****************TIME COMPLEXITY:{O(log(n))}***************
 -->Work : Apne niche wali saari nodes ko heap mein convert krta hai!!!!
 --> Kyuki sirf height pe depend krega!
 Approach:
 ->Jo index (0) bheja hai use largest element ka index man lia (Acc to max heap)
 ->fir uska left index and right index nikala
 ->Ab left and right mein jo bda hai us element se swap krdia
 ->dobara khud ko call krlia largest wale index ke sath
 */
void downHeapify2(vector<int> &arr,int n,int i)
{
    int largest=i;
    int left=(2*i)+1;
    int right=(2*i)+2;
    if(left<n&&arr[left]>arr[i])
    {
        largest=left;
    }
    if(right<n&&arr[right]>arr[i]&&arr[right]>arr[left])
    {
        largest=right;
    }
    if(i!=largest)
    {
        swap(arr[i],arr[largest]);
        downHeapify2(arr,n,largest);
    }
    
}
/*
 *****************TIME COMPLEXITY:{O(nlog(n))}***************
 -> n elements ko remove krege downHeapify(Ologn) se
 Approach:
 1.Akhiri index se loop chlana shuru kia
 2.swap kia first index wale element or akhiri index wale element ko(remaining array mein jo end mein h)!
 3.Hr call mein downheapify chla dia size ko ek se km krte krte(i) se !
 */
void heapSort(vector<int> &arr)
{
    int n = arr.size();
    for(int i=n-1;i>0;i--)
    {
        swap(arr[0], arr[i]);
        downHeapify2(arr,i,0); // 2nd argument size ka h
    }
}
/*
****************MAKING OUR OWN PRIORITY : MAX HEAP***********
 */
int main() {
    // insert code here...
    string str="abracadabra";
    cout<<"CHARACTER WITH MAXIMUM FREQUENCY:";
    char reschar=maxFrequency(str);
    cout<<reschar;
    /*int arr1[]={1,1,2,2,2,3,5};
    int arr2[]={1,1,1,2,2,4,5};
    cout<<"\n";
    cout<<"PRINTING THE COMMON ELEMENTS IN THE TWO ARRAYS:";
    getCommonElement1(arr1,7,arr2,7);*/
    /*
    cout<<"\n";
    cout<<"PRINTING THE COMMON ELEMENTS IN THE TWO ARRAYS ALONG WITH THE LEAST FREQUENCY:";
    getCommonElement2(arr1,7,arr2,7);*/
    /*cout<<"\n";
    cout<<"PRINTING THE LONGEST CONSECUTIVE SEQUENCE:";
    int arr3[]={10,5,9,1,11,8,6,15,3,12,2};
    vector<int> ans;
   ans=longestConsecutiveSequence(arr3,11);
    for(int j=0;j<ans.size();j++)
        cout<<ans[j]<<" ";*/
    /*cout<<"\n FINDING THE K LARGEST ELEMENTS IN THE ARRAY:";
    int arr[]={2,10,5,17,7,18,64};
    kLargestElements(arr,7,3);*/
    /*cout<<"\n SORT THE K SORTED ARRAY:";
    int arr[]={2,3,1,4,6,7,5,8,9};
    sortKSorted(arr,9,2);*/
   /* priority_queue<int> left;
     priority_queue<int,vector<int>,greater<int>> right;
     cout<<"IMPLEMENTING THE MEDIAN PRIORITY QUEUE:";
     addToMp(left,right,10);
     addToMp(left,right,20);
     addToMp(left,right,30);
     addToMp(left,right,50);
     addToMp(left,right,60);
     cout<<peekMp(left,right)<<"\n";
     cout<<removeMp(left,right)<<"\n";
      cout<<peekMp(left,right)<<"\n";*/
    /*cout<<"\n MERGING K SORTED LISTS";
     vector<vector<int>> lists={{10,20,30,40,50},{5,7,9,11,19,55,57},{1,2,3},{32,39}};
     vector<int> res;
    res= mergeKSortedLists(lists);
     for(int i=0;i<res.size();i++)
         cout<<res[i]<<" ";*/
    cout<<"\n CREATING OUR OWN MAX HEAP AND MIN HEAP:";
    vector<int> arr={10,20,30,25,5,40,35};
    // CreateMaxHeap(arr); // Using upHeapify
    BuildMaxHeap(arr);  // using downHeapify
    
   /* cout<<"\nCHECKING IF MAX HEAP IS CREATED OR NOT?";
    for(int i=0;i<7;i++)
        cout<<arr[i]<<" ";*/
    AddToMaxHeap(arr,50);
    AddToMaxHeap(arr,45);
    AddToMaxHeap(arr,70);
    /*cout<<"\nCHECKING IF ELEMENTS ARE ADDED TO MAX HEAP IS OR NOT?";
    cout<<"\n PRINTING THE MAX HEAP:";
    int n = arr.size();
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";*/
    /*cout<<"\nPEEK TO THE MAX HEAP:";
    cout<<peekToMaxHeap(arr);*/
    /*cout<<"\nREMOVE FROM THE MAX HEAP:";
    cout<<RemoveFromMaxHeap(arr);
    CHECKING IF ELEMENTS ARE REMOVED FROM MAX HEAP OR NOT?
    cout<<"\nMAX HEAP AFTER REMOVING A ELEMENT:";
    int n1 = arr.size();
    for(int i=0;i<n1;i++)
        cout<<arr[i]<<" ";*/
    /*cout<<"\nPEEK TO THE MAX HEAP:";
       cout<<peekToMaxHeap(arr);*/
    /*heapSort(arr);
    cout<<"\n PRINTING THE SORTED ELEMENTS USING HEAP SORT:";
    int n = arr.size();
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";*/
    return 0;
}
