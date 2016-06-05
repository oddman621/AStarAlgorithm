
namespace astarnode
{
    class constrants
    {
        public const float STRAIGHT = 1f;
        public const float DIAGONAL = 1.4f;
        public const float BASEDIST = 10f;

        public const char PASSABLE      = '□';
        public const char IMPASSABLE    = '▩';
        public const char OPENED        = '▣';
        public const char CLOSED        = '■';
        public const char STARTPOINT    = '☆';
        public const char DESTINATION   = '★';
        public const char FINALPATH     = '♥';
    }
    class node
    {
        public double f = 0, g = 0, h = 0;
        public int[] pos = { 0, 0 };
        public char tile = constrants.PASSABLE;
        public node shortest_route = null;
    }
    class linknode
    {
        public node data = null;
        public linknode prev = null;
        public linknode next = null;
        public linknode() { }
        public linknode(node data, linknode prev, linknode next)
        { this.data = data; this.prev = prev; this.next = next; }
    }
    class nodelist
    {
        //꼬리(마지막 노드의 next값)가 아닌, 마지막 요소를 가리킨다.
        private linknode firstelem = null;
        private linknode lastelem = null;
        
        //매개변수를
        private void insert(linknode beforedata, node data, linknode afterdata)
        {
            linknode temp = new linknode(data, beforedata, afterdata);
            //리스트의 머리쪽에서 insert되었는지 꼬리쪽에서 insert되었는지 판별
            //이를 이용해 firstelem과 lastelem을 올바르게 조정한다
            if (beforedata == null) firstelem = temp;
            if (afterdata == null) lastelem = temp;

            if (beforedata != null) beforedata.next = temp;
            if (afterdata != null) afterdata.prev = temp;
        }
        private node remove(ref linknode thenode)
        {
            if (thenode == null) return null;
            node retval = thenode.data;
            linknode beforenode = thenode.prev;
            linknode afternode = thenode.next;
            thenode = null;
            //리스트의 머리쪽에서 remove되었는지 꼬리쪽에서 remove되었는지 판별
            //이를 이용해 firstelem과 lastelem을 올바르게 조정한다
            if (beforenode == null) firstelem = afternode;
            if (afternode == null) lastelem = beforenode;

            if (beforenode != null) beforenode.next = afternode;
            if (afternode != null) afternode.prev = beforenode;
            return retval;
        }

        private void quick_sort_by_fval(linknode left, linknode right)
        {
            //구현 예정
        }
        private void bubble_sort_by_fval()
        {
            linknode it;
            linknode bubblelast = lastelem;

            while(bubblelast != firstelem)
            {
                it = firstelem;
                while(it.data != null)
                {
                    if(it.data.f > it.next.data.f)
                    {
                        node temp = it.data;
                        it.data = it.next.data;
                        it.next.data = temp;
                    }
                    if (it.next == bubblelast)
                        break;
                    it = it.next;
                }
                bubblelast = it;
            }
        }

        public void push_front(node data)
        {
            insert(null, data, firstelem);
        }
        public void push_back(node data)
        {
            insert(lastelem, data, null);
        }
        public node pop_front()
        {
            return remove(ref firstelem);
        }
        public node pop_back()
        {
            return remove(ref lastelem);
        }
        //좌표값이 같으면 같은 데이터이다.
        public linknode search(node data)
        {
            for (linknode it = firstelem; it != null; it = it.next)
                if (firstelem.data.pos[0] == data.pos[0] && firstelem.data.pos[1] == data.pos[1])
                    return it;
            return null;
        }

        public void SortByFval()
        {
            if (firstelem == null || lastelem == null) return;

            //quick_sort_by_fval(firstelem, lastelem);
            bubble_sort_by_fval();
        }
    }
    class nodemap
    {
        protected node[,] mapdata = null;

        public nodemap(){ }
        public nodemap(int x, int y) { CreateMap(x, y); }

        //해당 좌표가 유효한 지 검사
        private bool check_coord(int x, int y)
        {
            if (x < 0 || y < 0
                || x > mapdata.GetLength(1) 
                || y > mapdata.GetLength(0))
                return false;

            return true;
        }

        public node nodeptr(int pos_x, int pos_y)
        {
            if (mapdata == null) return null;
            if (!check_coord(pos_x, pos_y)) return null;
            return mapdata[pos_y - 1, pos_x - 1];
        }
        public void CreateMap(int size_x, int size_y)
        {
            mapdata = new node[size_y, size_x];
        }
    }
}