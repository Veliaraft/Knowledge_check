using System;
using System.IO;

namespace island_console{
    class Program{
        static void Main(string[] args){
            string[] file = File.ReadAllLines("island.txt");
            int[] island = new int[file.Length];
            for (int i = 0; i < file.Length; i++){
                island[i] = Convert.ToInt32(file[i]);
            }
            int waterCount = 0;
            int waterReserve = 0;
            int maxWall = 0;
            int secondMaxWall = 0;
            maxWall = island[0];
            for (int i = 1; i < island.Length; i++){
                if (island[i] >= maxWall){
                    maxWall = island[i];
                    waterCount += waterReserve;
                    waterReserve = 0;
                }
                else if (island[i] < maxWall){
                    waterReserve += (maxWall - island[i]);
                }
            }
            waterReserve = 0;
            secondMaxWall = island[island.Length - 1];
            for (int i = (island.Length - 2); secondMaxWall != maxWall; i--){
                if (island[i] < secondMaxWall){
                    waterReserve += secondMaxWall - island[i];
                }
                else if (island[i] >= secondMaxWall){
                    secondMaxWall = island[i];
                    waterCount += waterReserve;
                    waterReserve = 0;
                }
            }
            Console.WriteLine(waterCount);
            Console.ReadKey();
        }
    }
}
