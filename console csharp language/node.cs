
namespace astarnode
{
    class constrants
    {
        //각 노드간 거리에 사용된다.
        public const float STRAIGHT = 1f;
        public const float DIAGONAL = 1.4f;
        public const float BASEDIST = 10f;
        public const float STRAIGHT_DIST = STRAIGHT * BASEDIST;
        public const float DIAGONAL_DIST = DIAGONAL * BASEDIST;

        //타일표시에 이용된다.
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
        public node() { }
        public node(int x, int y) { pos[0] = x; pos[1] = y; }
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

        //lastelem이나 firstelem이 알맞은 값으로 설정되었는지 자동으로 확인/교정해준다.
        //다만 매개변수들이 올바른 값인지는 검사하지 않기 때문에
        //( - beforedata와 afterdata는 붙어있는가? )
        //( - 정말로 리스트의 beforedata와 afterdata 사이인가? )
        //( - data는 유효한 값인가? )
        //public으로 풀기엔 무리가 있는 것 같다.
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
            linknode left_it = left, right_it = right;
            node pivot = left_it.data;

            while(left_it != right_it)
            {
                while (left_it != right_it && right_it.data.f >= pivot.f) right_it = right_it.prev;
                if (left_it != right_it) left_it.data = right_it.data;
                while (left_it != right_it && left_it.data.f <= pivot.f) left_it = left_it.next;
                if (left_it != right_it) right_it.data = left_it.data;
            }
            //left_it(==right_it)는 중앙(pivot)을 가리키고 있다.
            left_it.data = pivot;
            if (left_it != left) quick_sort_by_fval(left, left_it.prev);
            if (left_it != right) quick_sort_by_fval(left_it.next, right);
        }
        //느린 정렬이지만 구현하기 쉬우면서도 안정적으로 작동하기에 failsafe 용도로 남겨둔다.
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
                if (it.data.pos[0] == data.pos[0] && it.data.pos[1] == data.pos[1])
                    return it;
            return null;
        }

        public void SortByFval()
        {
            if (firstelem == null || lastelem == null) return;

            quick_sort_by_fval(firstelem, lastelem);
            //bubble_sort_by_fval();
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
            if (x < 1 || y < 1
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
            for(int yi = 1; yi <= mapdata.GetLength(0); yi++)
                for(int xi = 1; xi <= mapdata.GetLength(1); xi++)
                    mapdata[yi - 1, xi - 1] = new node(xi, yi);
        }
    }
}