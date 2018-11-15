using System;
using System.Collections.ObjectModel;


namespace AppForInterview
{
    public class Node<T>
    {
        public Node() { }
        public Node(T data)
        {
            _data = data;
            _neighbors = null;
        }

        private T _data;
        private NodeList<T> _neighbors;

        public T Data
        {
            get { return _data; }
            set { _data = value; }
        }

        public NodeList<T> Neighbors
        {
            get { return _neighbors; }
            set { _neighbors = value; }
        }
    }

    public class NodeList<T> : Collection<Node<T>>
    {
        public NodeList() : base() { }
        public NodeList(int initialSize)
        {
            for (int i = 0; i < initialSize; i++)
            {
                base.Items.Add(default(Node<T>));
            }
        }
    }

    public class CircularLinkedListNode<T> : Node<T>
    {
        public CircularLinkedListNode() : base() { }
        public CircularLinkedListNode(T data) : base(data) { }
        public CircularLinkedListNode(T data, CircularLinkedListNode<T> previous, CircularLinkedListNode<T> next)
        {
            base.Data = data;
            base.Neighbors = new NodeList<T>(2);
            base.Neighbors[0] = previous;
            base.Neighbors[1] = next;
        }

        public CircularLinkedListNode<T> Previous
        {
            get
            {
                if (base.Neighbors == null)
                    return null;
                else
                    return (CircularLinkedListNode<T>)base.Neighbors[0];
            }
            set
            {
                if (base.Neighbors == null)
                    base.Neighbors = new NodeList<T>(2);

                base.Neighbors[0] = value;
            }
        }

        public CircularLinkedListNode<T> Next
        {
            get
            {
                if (base.Neighbors == null)
                    return null;
                else
                    return (CircularLinkedListNode<T>)base.Neighbors[1];
            }
            set
            {
                if (base.Neighbors == null)
                    base.Neighbors = new NodeList<T>(2);

                base.Neighbors[1] = value;
            }
        }
    }

    public class CircularLinkedList<T>
    {
        public CircularLinkedList()
        {
            _head = null;
            _tail = null;
            _count = 0;
        }

        private CircularLinkedListNode<T> _head;
        private CircularLinkedListNode<T> _tail;
        private int _count;

        public int Count { get { return _count; } }
        public CircularLinkedListNode<T> First { get { return _head; } }
        public CircularLinkedListNode<T> Last { get { return _tail; } }

        public CircularLinkedListNode<T> AddFirst(T data)
        {
            CircularLinkedListNode<T> tmp = new CircularLinkedListNode<T>();
            tmp.Data = data;

            if (_head == null)
            {
                _head = tmp;
                _tail = tmp;
                tmp.Previous = _head;
                tmp.Next = _tail;
                ++_count;
            }
            else
            {
                _head.Previous = tmp;
                tmp.Next = _head;
                tmp.Previous = _tail;
                _tail.Next = tmp;
                _head = tmp;
                ++_count;
            }
            return tmp;
        }

        public CircularLinkedListNode<T> AddLast(T data)
        {
            if (_tail == null)
            {
                return this.AddFirst(data);
            }

            CircularLinkedListNode<T> tmp = new CircularLinkedListNode<T>();
            tmp.Data = data;
            tmp.Previous = _tail;
            tmp.Next = _tail.Next;
            _tail.Next = tmp;           
            _tail = tmp;
            ++_count;

            return tmp;
        }

        public CircularLinkedListNode<T> AddBefore(CircularLinkedListNode<T> node, T data)
        {
            if (node == _head)
            {
                return this.AddFirst(data);
            }

            CircularLinkedListNode<T> tmp = new CircularLinkedListNode<T>();
            tmp.Data = data;
            tmp.Previous = node.Previous;
            tmp.Next = node;
            node.Previous = tmp;
            tmp.Previous.Next = tmp;
            ++_count;

            return tmp;
        }

        public CircularLinkedListNode<T> AddAfter(CircularLinkedListNode<T> node, T data)
        {
            if (node == _tail)
            {
                return this.AddLast(data);
            }
            CircularLinkedListNode<T> tmp = new CircularLinkedListNode<T>();
            tmp.Data = data;
            tmp.Next = node.Next;
            node.Next.Previous = tmp;
            node.Next = tmp;
            tmp.Previous = node;
            ++_count;

            return tmp;
        }

        public void Remove(CircularLinkedListNode<T> node)
        {
            if (node == null)
            {
                throw new ArgumentNullException();
            }

            node.Previous.Next = node.Next;
            node.Next.Previous = node.Previous;
            if (node == _head) { _head = node.Next; }
            if (node == _tail) { _tail = node.Previous; }
            node.Previous = null;
            node.Next = null;
            --_count;
            if (_count == 0)
            {
                _head = null;
                _tail = null;
            }

        }

        public CircularLinkedListNode<T> Find(T value)
        {
            CircularLinkedListNode<T> currentNode = _head;
            for (int i = 0; i < _count; i++)
            {
                if (currentNode.Data.Equals(value))
                    return currentNode;
                else
                    currentNode = currentNode.Next;
            }
            return null;
        }
    }

    class Program
    {
        public static void PrintValues(CircularLinkedList<int> cllist)
        {
            var currentNode = cllist.First;
            for (int i = 0; i < cllist.Count; i++)
            {
                Console.Write(currentNode.Data.ToString() + " ");
                currentNode = currentNode.Next;
            }
            Console.WriteLine();
        }

        static void Main(string[] args)
        {
            CircularLinkedList<int> cllist = new CircularLinkedList<int>();
            cllist.AddFirst(1);
            cllist.AddFirst(2);
            cllist.AddFirst(3);
            cllist.AddLast(100);
            PrintValues(cllist);

            CircularLinkedListNode<int> currentNode = cllist.First.Next;

            cllist.AddBefore(currentNode, 200);
            PrintValues(cllist);
            cllist.AddAfter(currentNode, 300);
            PrintValues(cllist);
            cllist.Remove(cllist.Find(200));
            PrintValues(cllist);

            Console.Read();
        }
    }
}
