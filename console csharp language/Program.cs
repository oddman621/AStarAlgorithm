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
            nodemap map = new nodemap(); SettingMap(ref map);
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
                        if (direction == null) continue;//갈 수 없는 곳일 경우
                        if (direction.tile == constrants.IMPASSABLE) continue;//이동이 불가능한 곳일 경우
                        if (closelist.search(direction) != null) continue;//이미 탐색된 곳일 경우

                        //발견되었지만 탐색한 적이 없는 곳일 경우
                        if(openlist.search(direction) != null)
                        {
                            int[] diff = { current.pos[0]-direction.pos[0], current.pos[1]-direction.pos[1] };
                            double distance_current_to_direction = (diff[0] != 0 && diff[1] != 0) ? constrants.DIAGONAL_DIST : constrants.STRAIGHT_DIST;
                            double current_g_plus_d_ctd = current.g + distance_current_to_direction;
                            if(direction.g > current_g_plus_d_ctd)//g값 비교 및 대입
                            {
                                direction.shortest_route = current; direction.g = current_g_plus_d_ctd;
                                direction.f = direction.g + direction.h;
                            }
                        }
                        else//발견되지 않은 곳일 경우
                        {
                            int[] diff = { Math.Abs(current.pos[0] - direction.pos[0]), Math.Abs(current.pos[1] - direction.pos[1]) };

                            //g값 산출 및 대입
                            direction.g = current.g + ((diff[0] != 0 && diff[1] != 0) ? constrants.DIAGONAL_DIST : constrants.STRAIGHT_DIST);

                            //h값 산출 및 대입
                            diff = new int[2]{ Math.Abs(direction.pos[0] - userdefine.DESTINATION_X), Math.Abs(direction.pos[1] - userdefine.DESTINATION_Y) };
                            while (diff[0] >= 1 && diff[1] >= 1)
                            { diff[0] -= 1; diff[1] -= 1; direction.h += constrants.DIAGONAL_DIST; }
                            while(diff[0]-- >= 1)
                                direction.h += constrants.STRAIGHT_DIST;
                            while(diff[1]-- >= 1)
                                direction.h += constrants.STRAIGHT_DIST;

                            //최종 f값 산출 및 대입
                            direction.f = direction.g + direction.h;
                            if (direction.tile != constrants.DESTINATION && direction.tile != constrants.STARTPOINT)
                                direction.tile = constrants.OPENED;

                            direction.shortest_route = current;
                            openlist.push_front(direction);
                        }
                    }

                //길찾기 과정 출력
                for (int yi = 1; yi <= userdefine.MAPSIZE_Y; yi++)
                {
                    for (int xi = 1; xi <= userdefine.MAPSIZE_X; xi++)
                        Console.Write(map.nodeptr(xi, yi).tile);
                    Console.WriteLine();
                }
                Console.WriteLine();

                openlist.SortByFval();
            }
            //길 탐색 끝

            //최적 루트 표시 및 결과 출력
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
