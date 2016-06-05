using System;

namespace userdefines
{
    class userdefine
    {
        public const int MAPSIZE_X = 7;
        public const int MAPSIZE_Y = 5;
        public const int STARTPOINT_X = 2;
        public const int STARTPOINT_Y = 3;
        public const int DESTINATION_X = 6;
        public const int DESTINATION_Y = 3;
        public static readonly int[,] OBSTACLE_LIST = { { 4, 2 }, { 4, 3 }, { 4, 4 } };
    }

    //모두 정상일 시 true
    static class check_userdefines
    {
        public static bool CHECK_USERDEF_MAPSIZE()
        {
            return userdefine.MAPSIZE_X > 0 && userdefine.MAPSIZE_Y > 0;
        }
        public static bool CHECK_USERDEF_COORD(int X, int Y)
        {
            return (X > 0 && X <= userdefine.MAPSIZE_X) && (Y > 0 && Y <= userdefine.MAPSIZE_Y);
        }
        public static bool CHECK_USERDEF_STARTPOINT()
        {
            return CHECK_USERDEF_COORD(userdefine.STARTPOINT_X, userdefine.STARTPOINT_Y);
        }
        public static bool CHECK_USERDEF_DESTINATION()
        {
            return CHECK_USERDEF_COORD(userdefine.DESTINATION_X, userdefine.DESTINATION_Y);
        }
        public static bool CHECK_USERDEF_OBSTACLE_LIST()
        {
            for (int i = 0; i < userdefine.OBSTACLE_LIST.GetLength(0); i++)
                if (!CHECK_USERDEF_COORD(userdefine.OBSTACLE_LIST[i, 0], userdefine.OBSTACLE_LIST[i, 1]))
                    return false;
            return true;
        }

        public static bool CHECK_USERDEF_PROGRESS()
        {
            if(!CHECK_USERDEF_MAPSIZE())
            {
                Console.WriteLine("맵사이즈가 올바르지 않습니다. 현재 맵사이즈의 값은 X = {0}, Y = {1} 입니다.", userdefine.MAPSIZE_X, userdefine.MAPSIZE_Y);
                return false;
            }
            if(!CHECK_USERDEF_STARTPOINT())
            {
                Console.WriteLine("시작점이 올바르지 않습니다. 현재 시작점의 값은 X = {0}, Y = {1} 입니다.", userdefine.STARTPOINT_X, userdefine.STARTPOINT_Y);
                return false;
            }
            if(!CHECK_USERDEF_DESTINATION())
            {
                Console.WriteLine("도착점이 올바르지 않습니다. 현재 도착점의 값은 X = {0}, Y = {1} 입니다.", userdefine.DESTINATION_X, userdefine.DESTINATION_Y);
                return false;
            }
            if(!CHECK_USERDEF_OBSTACLE_LIST())
            {
                Console.WriteLine("장애물 위치가 올바르지 않습니다. 현재 장애물 위치의 값은 다음과 같습니다:");
                for (int i = 0; i < userdefine.OBSTACLE_LIST.GetLength(0); i++)
                    Console.Write("({0}, {1}) ", userdefine.OBSTACLE_LIST[i, 0], userdefine.OBSTACLE_LIST[i, 1]);
                return false;
            }

            Console.WriteLine("모든 유저값이 정상입니다.");
            return true;
        }
    }
}
