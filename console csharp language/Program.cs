using System;

using astarnode;
using userdefines;

namespace console_csharp_language
{
    class Program
    {
        static void SettingMap(ref nodemap map)
        {
            map.CreateMap(userdefine.MAPSIZE_X, userdefine.MAPSIZE_Y);
            map.nodeptr(userdefine.STARTPOINT_X, userdefine.STARTPOINT_Y).tile = constrants.STARTPOINT;
            map.nodeptr(userdefine.DESTINATION_X, userdefine.DESTINATION_Y).tile = constrants.DESTINATION;
            for (int i = 0; i < userdefine.OBSTACLE_LIST.GetLength(0); i++)
                map.nodeptr(userdefine.OBSTACLE_LIST[i, 0], userdefine.OBSTACLE_LIST[i, 1]).tile = constrants.IMPASSABLE;
        }

        static void Main(string[] args)
        {
            //입력된 값의 유효성 확인
            if (!check_userdefines.CHECK_USERDEF_PROGRESS()) return;

            //데이터 준비
            nodemap map = null; SettingMap(ref map);
            nodelist openlist = new nodelist(), 
                closelist = new nodelist();
            node current = null;
            openlist.push_front(map.nodeptr(userdefine.STARTPOINT_X, userdefine.STARTPOINT_Y));
            //데이터 준비 끝

            //길 탐색 시작
            while((current = openlist.pop_front()) != null)
            {
                closelist.push_front(current);
                if(current.tile == constrants.DESTINATION) break;
                if(current.tile != constrants.STARTPOINT)
                    current.tile = constrants.CLOSED;

                for(int ySubVal = 1; ySubVal >= -1; ySubVal--)
                    for(int xSubVal = -1; xSubVal<=1; xSubVal++)
                    {
                        node direction = map.nodeptr(current.pos[0] + xSubVal, current.pos[1] + ySubVal);
                        if (direction == null) continue;
                        if (direction.tile == constrants.IMPASSABLE) continue;
                        if (closelist.search(direction) != null) continue;

                        if(openlist.search(direction) != null)
                        {
                            int[] diff = { current.pos[0]-direction.pos[0], current.pos[1]-direction.pos[1] };
                            float distance_current_to_direction

                        }
                    }

                openlist.SortByFval();
            }
            //길 탐색 끝

            //최적 루트 표시 및 맵 출력
            node bestroute = current;
            if (bestroute != null)
            {
                while (bestroute.shortest_route != null)
                {
                    bestroute.tile = constrants.FINALPATH;
                    bestroute = bestroute.shortest_route;
                }
                bestroute.tile = constrants.FINALPATH;
            }
            for(int yi = 1; yi <= userdefine.MAPSIZE_Y; yi++)
            {
                for(int xi = 1; xi <= userdefine.MAPSIZE_X; xi++)
                    Console.Write(map.nodeptr(xi, yi).tile);
                Console.WriteLine();
            }
            //최적 루트 표시 및 맵 출력 끝
        }
    }
}
