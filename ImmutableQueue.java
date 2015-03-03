class node<E>{      //a new class formed
E data;
node next;
};

public class ImmutableQueue<E>{
node head,tail;
int size;

public ImmutableQueue(){
    head = null;
    tail = null;
    size = 0;
}

public ImmutableQueue<E> enqueue(E e)
{
    ImmutableQueue<E> Q = new ImmutableQueue<E>();
    node<E> newnode = new node<E>();        //create a new node and allocate memory to it
    newnode.data = e;
    newnode.next = null;

    if(head==null)                  //initial queue was empty
    {
        Q.head = newnode;
        Q.tail = newnode;
        Q.size = size + 1;
    }
    else if(tail.next==null)        //tail of queue points to last node in sequence
    {
        Q.head = head;
        Q.tail = newnode;
        Q.size = size + 1;
        tail.next = newnode;
    }
    else                            //insertion of data such that tail of input queue doesnot point to last element of data sequence
    {
        node temp = head;
        int local_size = 1;
        newnode.data = (E)temp.data;
        newnode.next=null;
        Q.head = Q.tail = newnode;

        while(true)
        {
            if(temp==tail)
                break;
            temp = temp.next;
            newnode.data = (E)temp.data;
            newnode.next=null;
            local_size++;
            Q.tail.next = newnode;
            Q.tail = newnode;
        }
        //node<E> newnode = new node<E>();
        newnode.data = e;
        newnode.next=null;
        local_size++;
        Q.tail.next = newnode;
        Q.tail = newnode;
        Q.size = local_size;
    }
    return Q;           //returning queue
}


public ImmutableQueue<E> dequeue()
{
    ImmutableQueue Q = new ImmutableQueue();
    if(head==null)              //already queue is null
        return null;
    else if(head == tail)       //size of this queue is 1
    {
        Q.head = Q.tail = null;
        Q.size = size - 1;
    }
    else                        //size of queue is greater than 1
    {
        Q.head = head.next;     //set head of new queue as next to present head
        Q.tail = tail;
        Q.size = size - 1;
    }
    return Q;
}

public E peek()
{
    if(head==null)          //empty queue
        return null;
    return (E)head.data;    //returns data at front of queue
}


public void print_queue()   //prints data of this queue
{
    node temp = head;
    if(temp!=null)
    {
        while(true)
        {
            System.out.printf("%d ",(int)temp.data);
            if(temp==tail) break;
            temp = temp.next;
        }
    }
}

public int size()
{
    if(head==null)      //queue is empty
        return -1;
    return size;
}

public static void main(String[] args)
{

//Testing ImmutableQueue class by some examples

/*
    ImmutableQueue<Integer> Q = new ImmutableQueue<Integer>() ;
    ImmutableQueue Q1;

    System.out.printf("\nQueue contents are as follows: \n");
    Q.print_queue();

    Q1 = Q.enqueue(1);
    System.out.printf("\nQueue contents are as follows: \n");
    Q1.print_queue();

    Q1 = Q1.enqueue(2);
    System.out.printf("\nQueue contents are as follows: \n");
    Q1.print_queue();

    Q1 = Q1.enqueue(1);
    System.out.printf("\nQueue contents are as follows: \n");
    Q1.print_queue();

    Q1 = Q1.enqueue(1);
    System.out.printf("\nQueue contents are as follows: \n");
    Q1.print_queue();

    Q1 = Q1.dequeue();
    System.out.printf("\nQueue contents are as follows: \n");
    Q1.print_queue();
*/
}

}
