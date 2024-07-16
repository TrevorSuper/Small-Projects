// From this video: https://www.youtube.com/watch?v=Dkn4EKL2xSE
/*
Leaks and Overruns:

The heap is not your friend.
All threads in your application share the same process heap. Allocating and deallocating
memory locks the process heap until those operations complete. Slow down.
Allocating on the stack avoids this entirely.
Lots of available memory makes programmers sloppy.

Example: City or station codes at airports: LAX Los Angeles
Three characters long
char szStationCode[8] = {0};

void DoSomethingWithCity(const char *cpszCityCode)
{
  OurStringClass sStationCode(cpszCityCode);
}

This string class instance has to copy the constructor argument and allocates from the
heap. 8 chars of data carved off the heap into a chunk. Heap management code expends
its own memory to track this and all other chunks.

When this station code string is done being used, it goes back into the free list.
Breaking the heap down into smaller chunks is called fragmentation. This is no different
in garbage collected langauges. Most heap management libraries will not attempt to
reallocate the heap? I think he is trying to say.

After a lot of fragmentation the heap may not be able to allocate new memory without
reallocating old memory. Nothing will get done until the heap has finished reallocating.
This can take a long time or in an extreme case this is enough to bring down a server.

Loops
std::vector<MyData> myData;
for_each(myData.begin(),myData.end(),myProcess);

void myProcess(myData)
{
  MyDataManager *pMgr = new MyDataManager(MyData);
  .
  .
  delete pMgr; // If you remember!
}

If the code between the new and delete is long enough or something changes in a later
release to exit this loop prematurely, this code will leak.

std::vector<MyData> myData;
for_each(myData.begin(),myData.end(),myProcess);

void myProcess(myData)
{
  MyDataManager mgr(MyData);
  .
  .
  .
}

Avoid creating an instance inside a loop, but if you must, this rewrite won't leak.


If you're not taking the higher order function path this
OurStringClass temp;
for(int i = 0; i < iMaxStrings; ++i){
  temp = buffers[i];
}

is better than this

OurStringClass temp;
for(int i = 0; i < iMaxStrings; ++i){
  OurStringClass *temp = new OurStringClass(buffers[i]);
}

Do not use the latest thing if you do not need to!
string str = cpszArg;

old school:
char szStr[45];
strcpy_s(szStr, sizeof(szStr), cpszArg);
If you're not going to do string magic with data in the buffer, do not use a string to
store it. This will create extra work for the program to do for no useful benefit.


Index operators don't have range checking. at methods have range checking.
myVec[0]
myVec.at(0)

Speed or safety? Crashing, the ultimate slowdown?

*/

// Search starting at the end of the range and not walk off the front

template <class T> int lastIndexOf(const T *pData, size_t extent, T target){
  size_t uRet = extent - 1; // set it up at the end of the range
  const T *pTest = pData + uRet; // start at that point
  while (pTest >= pData){ // walking backward making sure to not get past the beginning, test pointer must always be >= the beginning
    if (*pTest-- == target){
      return static_cast<int>(uRet);
    }
    --uRet;
  }
  return -1; // the only unacceptable return value for an index since we know we can't go past the beginning
}
/*
Nobody ever has an array of 4 billion to search.
Explicit range checking. Not slow. Only occurs during initialization.
We don't have to test the range of the pointer during each iteration because it's bounded.
It can only fall within the range of data we've been asked to test.

Another way to look for errors is to abstract your memory management through functions
that allow inspecting the memory for overruns and underruns once they've been used.
Some debug runtimes do this already.
*/

/*   Memory Leaks - Just don't write them he says
The Sandwich Pattern

In C, it's malloc followed by working code followed by free

char *pBuffer = malloc(32000); 
if (pBuffer){
  doSomethingWith(pBuffer);
  free(pBuffer);
}

In C++, it's new followed by working code followed by delete

char *pBuffer = new (nothrow) char [32000];
if (pBuffer){
  doSomethingWith(pBuffer);
}
delete [] pBuffer;

later maintenance code could cause the free or delete to be skipped
an exception throw locally but handled farther up the call chain could leak
Don't use the sandwich pattern? Use auto pointer, shared pointer, or unique poiner.
These will garuantee, as much as possible, that memory is cleaned up in future releases.

a way to write a leak in destructors that sneaks up on you.
forgetting to maintain the virutal destructor chain.
At object destruction time, the generated code works its way up the derivation chain,
but stops at the first non-virtual destructor. This can abandon memory and resources,
allocated by parent classes all the way up to the base class.

*/

// virtual destructor chain
class c03_code {
  public:
    c03_code(arguments);
    virtual ~co3_code();

    /* data */
};

class c04_code {
  public:
    c04_code(arguments) : c03_code() {}
    ~c04_code(); // coder for class c04_code forgot the virtual keyword here
    /* any memory allocated by c03 will be leaked during destruction.
    This can be difficult to track down because coders will look at the individual
    destructors in the cpp file and assure themselves all the memory has been 
    released, but forget to look in the header file to make sure the keyword virtual
    didn't get dropped along the way.
    */
    /* data */
};

class c05_code {
  public:
    c05_code(arguments) : c04_code() {}
    virtual ~c05_code();

    /* data */
};

/*  Function calls and method calls with objects
Don't pass objects through call interfaces to access just one feature of a class.
If you need to pass an object through a call interface pass a reference or a pointer.
If you have to allocate off the heap, use the standard template library wrappers to
manage class instances. These handle copy and move semantics as well.
*/

void MyMethod(SomeResourceType resource){ // sandwich
  MyClass *myInstance = new MyClass(resource);
  .
  delete myInstance;
}

void MyMethod(SomeResourceType resource){ // cleaned up automatically
  auto_ptr<MyClass> myInstance (new MyInstance(resource));
  .
}

void MyMethod(SomeResourceType resource){
  MyClass myInstance(resource);
  // no need to clean up, allocated on stack
} // should not allocate no stack if class has a large memory footprint, 32kb?
// classes with large memory footprints should be rare in practice

/*
Do third party libraries factory methods clean up after themselves, or do they expect you to?
Three methods of approach
1. Receive a pointer to an object and delete it when you're done.
2. The factory exports a method you can call to return the instance for clean up.
3. The factory returns an auto pointer based instance that cleans itself when it goes out of scope.
*/

class Guest {
  public:
    Guest();
    Guest(const char *name);
    void programLevel(int level);
  private:
    string m_name;
    int m_level;
};

class Room {
  public:
    Room();
    Room(const char *number);
    void type(int name);
  private:
    string m_name;
    int m_level;
};

class Reservation {
  public:
    Reservation();
    Guest *getGuest(int guestIndex); // the reservation class manages these two lifetimes, so users of the class won't have to
    Room *getRoom(int roomIndex);
    int guestCount();
    int roomCount();
};

Reservation *LoadReservation(const char *reservationKey); // factory class?
/* the factory does not manage the lifetime of the reservation instance
accessing a room or guest has different semantics than accessing a reservation. Maintenance coders will tend to
assume if they don't have to manage the lifetime of the guest or room instances, they don't have to manage the 
reservation itself. Nothing is keeping you from using auto pointer against the returned pointer.

Today when people receive a string buffer they expect to use delete, not free.
To solve this write a wrapper class that accepts a pointer to the class with the unfortunate memory management, and
capture what it returns in that class. When the code invokes your wrappers destructor, clean up the pointer to
the captured data in the manner appropriate to the class.
*/

class BufferWrap{
  public:
    BufferWrap(Buffer *pb) : m_pb(pb), m_pText(0){}
    ~BufferWrap(){
      if (m_pText){
        free(m_pText);
      }
    }

    char *getString(){
      return (m_pText) ? m_pText : (m_pText = pb -> getStringBuffer());
    }

  private:
    Buffer *m_pb;
    char *m_pText;
};

Buffer buffr;
BufferWrap wrap(&buffr);

buffr << some_stuff;

text_handler(wrap.getString());

/*   Two kinds of delete in C++ object delete and array delete. A compiler may not flag an inappropriate use of delete
when array is more correct. If the array happens to contain objects there destructors won't be called with object
delete leading to leaks.  */

class X {
  public:
    X(int x) : m_x(x) {}
    X() : m_x(0) {}
    ~X();
  private:
  int m_x;
};

int _tmain(int argc, _TCHAR* argv[]){
  X *pX = new X[34];
  delete [] pX;
  return 0;
}
// Document the memory management requirements of your classes and functions in an easy to understand way.

/* Pointers, no do-overs
The re-use of deleted pointers is usually never written into code, but maintenance coders can introduce this.
if (someCondition()){
  delete pSomething;
  // probably should have returned here but didn't.
}
.
20-50 lines later
.
int idx = pSomething -> getFirstIndex();

the most common cause of this is functions that are too long or too complex.
Maintenance coders on a tight deadline don't look too far away from the sight of the defect they've been
tasked to fix. This can slip through build phases if the warning level of the compiler isn't high enough,
or if the compiler doesn't check at all. The Problem: The now deleted pointer could still point to useful
memory and may even have the same value that was there when it was deleted. In multithreaded applications,
unit testing of the logic flow may or may not be able to produce enough threads to cause heap changes during
the tests. In single threaded code this might work as if nothing went wrong. In multihreaded this problem
can have different effects each time its reported making it hard to track down. The delete operator
severs the relationship between the pointer and the memory to which it pointed, unless the code erases the
memory itself before the delete operation. Else the heap manager will eventually reclaim the block.
Static Analysis tools cpplint. C/C++ code checker looking for bad coding practices. If not using static
analysis tools, unit testing can help reveal this issue. Set the deleted pointer back to null in any
non-terminal portion of the code, that is if you're not at the end of the function or about to execute a
return statement.

if (someCondition()){
  delete pSomething;
  pSomething = null;
  // probably should have returned here but didn't.
}
.
20-50 lines later
.
int idx = pSomething -> getFirstIndex();

Any attempt to dereference this pointer will cause an exception. Unit testing should hit all code paths.
Gimple PC lant and flexilint. Source Forge cppcheck. Do not rely on just one tool or method of testing.
*/

/* 
You do not have a trust relationship with code. Software does not exist in a vaccuum. Initialize everything.

if (myWorkPtr == null){
  // initialize the pointer
}
myWorkPtr -> work();

This code works in a debug build and fails in a release build, because the pointer conetains what is on the stack
in the data. The debug build puts null into this pointer. Not just pointers and buffers, also applies to intergral
values used as offsets or indexes and booleans used as branching gates. Set pointers to null, integers and
characters to something reasonable in your context, and booleans appropriate to the purposes. In C++ it is safe
to delete a null pointer. If you never allocate memory using a particular pointer variable, it's safe to delete
at the end of the scope or in the destructor. In C calling free on an uninitialized pointer is a bad idea. C++
still has the old malloc behavoir.
- Never assume an allocation will work. Either use exception handling, or test for a null result, or whatever
works in the environment.
- Don't assume that the arguments to your function will always contain valid data, particularly when the caller
passes a pointer.
- If you're writing a web app, never trust your inputs. (Overrun haven)
If you have to use fixed length buffers in some part of your code, length test the incoming data. Truncate or reject.
If possible exchange fixed length buffers for something more adaptable and safe.
- If your compiler supports safe string memory libraries, use the functions in them whenever possible. Microsoft has
a set of safe string and memory functions designed to prevent ovveruns.
https://msdn.microsoft.com/en-us/library/windows/desktop/ff468908(v=vs.85).aspx
redirects to here:
https://learn.microsoft.com/en-us/windows/win32/menurc/string-overviews
*/

// Classic mistake below, usually maintenance coders, use before test
int someFunction(struct data *pData){
  SomeObject *pObeject  = new SomeObject(pData);
  int numDataFields = pObject -> numDataObjects;
  if (!pObject){
    return -1;
  }
  .
  .
  .
  // retVal gets set
  delete pObject;
  return retVal;
}
/*
Original code almost always forgot to check to ensure that the object was allocated properly and someone came in
afterward to put in the safety check.
*/
int someFunction(struct data *pData){
  auto_ptr<SomeObject> pObject (new SomeObject(pData));
  int numDataFields = 0;
  retVal = -1;
    if (pObject){
      numDataFields = pObject -> numDataObjects;
      .
      .
      // retVal gets set
    }
  return retVal;
}

int someFunction(struct data *pData){
  auto_ptr<SomeObject> pObject (new SomeObject(pData));
  int numDataFields = 0;
  retVal = -1;
  try {
    pObject = new SomeObject(data);
  }
  catch (std::bad_alloc & ba){
    return retVal;
  }
  numDataFields = pObject -> numDataObjects;
  .
  .
  // retVal gets set
  return retVal;
}
/*
Trust nothing? Paranoia? Guarded approach to allocations and incoming data is what works in a world of hackers.
It is correct so set up contracts with those who call your code and to doubt that your callers aren't following
that contract.

Defensive programming: threat or menace?
*hides defects
*lowers performance
- Do it
Application that don't check every detail of their applications are vulnerable to hacking.
Hackers don't force you down an incorrect logic path, they do it by gaining access to memory through unchecked buffers.
Could create a dos attack. Your customers do not want an application that crashes.
You can remark defective function inputs or other exceptions in your debugging logs (and you should read those logs)
Unit and system testing should exercise all code paths. Specific test cases for edge and corner case data inputs
should be present. Your QA team shouldn't be afraid to write tested destruction cases into their plans.
Defensive programming is not pretty, but it works. In my own words you hate it when you need it, but loathe
the fact you didn't implement this when you have a serious issue arise.
*/

/* Simultaneous Data Access (multithread)

The abstracted interface always hands back copies of data not the actual data. Handing over the address of a string
or a character array or a pointer to a data object is asking for someone to make a mistake and modify the data.
*/

#include "CMutex.h"
////////////////////////////////////////////////////////////
class CMutexHelper {
  public:
    CMutexHelper(CMutex *mutex) : m_mutex(mutex), m_locked(false) {
      lock();
    }

    CMutexHelper() : m_mutex(null), m_locked(false) {}
    void use(CMutex *mutex){
      m_mutex = mutex;
      lock();
    }

#if !defined(TRY_ONLY)
  bool try (CMutex *mutex = null){
    if (mutex){
      m_mutex = mutex;
    }
    m_locked = (m_mutex) ? m_mutex -> Try() : false;
    return m_locked;
  }
#endif

    ~CMutexHelper(){
      if (m_mutex && m_locked){
        m_mutex -> Release();
      }
    }

    bool isLocked() { return m_locked; }
  private:
  CMutex *m_mutex;
  bool m_locked;

  void lock(){
    if (m_mutex){
#if defined(TRY_ONLY)
        m_locked = m_mutex -> Try();
        if (!m_locked) {
          throw 1;
        }
#else
        m_locked = true;
        m_mutex -> Lock();
#endif
    }
  }
}; // Using synchronized code always runs the risk of a deadlock

void MyClass::SyncedMethod(){
  CMutexHelper mth;
  try {
    mth -> use(&m_myMutex);
    DoSomethingWithSynchAsset();
    SomeMoreCode();
  }
  catch (int){
    // log it or deal with it
  }
}

void MyClass::OtherSyncedMethod(){
  CMutexHelper mth;
  try {
    mth -> use(&m_myMutex);
    DoSomethingElseWithSynchAsset();
    StillAnotherFunctionCall();
  }
  catch (int){
    // log it or deal with it
  }
}

// These two above methods are safe when called individually, but should never call each other.

void myClass::SychronizedMethod(){
  CMutexHelper mth;
  try {
    mth -> use(&m_myMutex);
    private_workMethod();
  }
  catch (int) {
    // log it or deal with it
  }
}

void myClass::private_workMethod(){
  DoSomethingWithSyncAsset();
  SomeMoreCode();
}

class CMutexUser {
  public:
    CMutexUser() {}

    virtual ~CMutexUser(){
      release();
    }

    bool try(){
      return (m_mutex.isLocked()) ? true : m_mutex.Try();
    }

    bool release(){
      if (m_mutex.isLocked()){
        m_mutex.Release();
      }
    }

  private:
    CMutex m_mutex;
};

class MyMutexedClass : public CMutexUser(){
  MyMutexedClass() : CMutexUser(){}
  virtual ~MyMutexedClass(){}
  void someMethod(){
    if (try()){
      // work
      release(); // do this or risk being locked out
    } else {
      // note that work wasn't done or try again
    }
  }
};

// Undefined behavior and other bad practices
int i = 0;
for(; i < 20; ++i){ // loop indexes can easily end up in an off-by-one error in an unsafe direction
  doThing(someVar[i]); // 2 common causes are incorrect pointer arithmetic and code that tries to be clever with
}                      // loop index variables

int i = 0;
for(; i < 20; ++i){
  if (someTest(i)) { // either the compiler should be in control or the programmer should be in control not the two
    ++I;             // of you together. If you need to manage the index yourself use while or do while
  }                  // avoid too much code inside one loop
  doThing(someVar[i]);
}

void doWork(int i){
  // do some work
}

vector<int> someInts; // to avoid out of range errors you can use vectors with STL iterators in the for each function
fillVector(vector);
for_each(someInts.begin(), someInts.end(), doWork);

const CDatum = *cpDatum;

while (null != (cpDatum = getNextDatum())){ // when you can avoid it don't instance classes inside a loop
  serviceProvider sp;
  sp.performService(cpDatum);
  .
  .
}

const CDatum = *cpDatum; // this second way is faster and cleaner
serviceProvider sp;

while (null != (cpDatum = getNextDatum())){
  sp.performService(cpDatum);
  .
  .
}

#include <stdio> // header files can lead less experienced coders to think they might be able to access data that
#include <string> // isn't theirs by doing a little pointer math, particulary on parts of the class you declared
#include "SampleFramework.h" // to be private

/*
If you're trying to be clever, don't. If you look at a piece of code and congratulate yourself on how clever or tricky
it is rather than how correct it is, do it over. Being clever is just being stupid.
*/

/*   Rules and Guidlines
- If data doesn't have to come from the heap, dont take it from the heap.
- When data or classes have to come from the heap, use the STL wrapper classes to ensure that everything is cleaned up.
(make share c++11 and make unique from c++14 to generate pointers)
- Manage data access through abstract interfaces.
- Write boring code.
- Make your solution fit the problem, not the other way around.
- If you're uncomfortable with a technique, or feel that you don't understand it fully-don't use it!
- Comment your code.
- Read everything you can find on C++ code.
*/