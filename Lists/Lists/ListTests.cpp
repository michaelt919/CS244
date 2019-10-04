#include "ArrayList.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

void removeNegatives(LinkedList<double>& list)
{
    while (!list.isEmpty() && list.getFirst() < 0)
    {
        list.removeFirst();
    }

    auto i = list.begin();
    while (i.hasNext())
    {
        if (i.peekNext() < 0)
        {
            i.removeNext();
        }
        else
        {
            i++;
        }
    }
}

int main()
{
    cout << "ArrayList: " << endl;
    {
        ArrayList<double> list{ 4 };
        ArrayList<double>& clist{ list };

        double init[8] = { 1.0, 1.5, 2.0, 2.5, 3.5, 4.0, 4.5, 5.0 };

        cout << "Add eight values at end:\n";
        list.addAll(init, 8);

        cout << list << endl;

        ArrayList<double> listCopy{ list };

        cout << "Copied list:\n";
        cout << listCopy << endl;

        ArrayList<double> listCopy2{ 4 };
        listCopy2 = list;

        cout << "Copied list:\n";
        cout << listCopy2 << endl;

        cout << "Set element 4 to 3.14:\n";
        list[4] = 3.14;
        cout << clist << endl << endl;

        cout << "Get element at index 1: " << clist[1] << endl << endl;

        cout << "Insert 9.0 at position 3, and -5.0 at position 0:\n";
        list.add(3, 9.0);
        list.add(0, -5.0);
        cout << clist << endl << endl;

        cout << "Insert 0.5, 1.5, 2.5 at position 0:\n";
        double toAdd[3] = { 0.5, 1.5, 2.5 };
        list.addAll(0, toAdd, 3);
        cout << clist << endl << endl;

        cout << "Add 99.0:\n";
        list.add(99.0);
        cout << clist << endl << endl;
                
        cout << "Copied list:\n";
        cout << listCopy << endl;

        cout << "Copied list:\n";
        cout << listCopy2 << endl;
    }

    cout << endl;

    cout << "Linked List:" << endl;
    {

        LinkedList<double> list;
        const LinkedList<double>& clist{ list };

        double init[8] = { 1.0, 1.5, 2.0, 2.5, 3.5, 4.0, 4.5, 5.0 };

        cout << "Add eight values:" << endl;
        for (int i = 7; i >= 0; i--)
        {
            list.addFirst(init[i]);
        }

        cout << list << endl << endl;

        cout << "Using for loops:" << endl;

        for (LinkedListIterator<double> i = clist.begin(); i != clist.end(); i++)
        {
            double x = *i;
            cout << x << endl;
        }

        cout << endl;

        for (MutableLinkedListIterator<double> i = list.begin(); i != list.end(); i++)
        {
            double x = *i;
            cout << x << endl;
        }

        cout << endl;

        for (double x : clist)
        {
            cout << x << endl;
        }

        cout << endl;

        for (double& x : list)
        {
            x = x + 1;
        }

        for (double x : list)
        {
            cout << x << endl;
        }

        cout << endl << endl;

        cout << "Get first element: " << clist.getFirst() << endl << endl;

        cout << "Add 99.0:\n";
        list.addFirst(99.0);
        cout << clist << endl << endl;

        cout << "Remove 3 elements:\n";
        list.removeFirst();
        list.removeFirst();
        list.removeFirst();
        cout << clist << endl << endl;

        cout << "Remove all:\n";
        list.clear();
        cout << clist << endl << endl;
    }

    cout << "Testing removeNegatives():" << endl;
    {

        LinkedList<double> list;

        for (int i = 0; i < 16; i++)
        {
            list.addFirst((rand() % 2049) / 1024.0 - 1.0);
        }

        cout << list << endl;

        removeNegatives(list);

        cout << list << endl;

        cout << endl;
    }

    return 0;
}
