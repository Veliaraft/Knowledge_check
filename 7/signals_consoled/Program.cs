using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;


namespace signals_consoled {
    public class Signals{
        public List<int> time = new List<int>();
        public List<bool> state = new List<bool>();
        public int counter;
        public int Min = 0;
        public int Max = 0;
        public float Middle = 0f;
        public float Hz = 0f;
    }
    class Program {
        static int Main(string[] args) {
            //Read the file;
            if (!File.Exists("signals.bin")){ Console.WriteLine("File doesn't exist. Please, put a file in program directory and retry."); return 0;}
            Byte[] BytesList = File.ReadAllBytes("signals.bin");
            int[] TimeArr = new int[BytesList.Length/3];
            float AllTime = 0;
            //

            Signals first = new Signals();
            first.state.Add(Convert.ToBoolean(BytesList[2] & (1 << 2)));
            first.time.Add(BytesList[0] << 8 | BytesList[1]);
            
            Signals second = new Signals();
            second.state.Add(Convert.ToBoolean(BytesList[2] & (1 << 4)));
            second.time.Add(BytesList[0] << 8 | BytesList[1]);
            
            Signals third = new Signals();
            third.state.Add(Convert.ToBoolean(BytesList[2] & (1 << 7)));
            third.time.Add(BytesList[0] << 8 | BytesList[1]);
            for (int i = 3; i < BytesList.Length; i += 3) {
                if ((Convert.ToBoolean(BytesList[i + 2] & (1 << 2))) != first.state[first.counter]) {
                    first.counter++;
                    first.state.Add(Convert.ToBoolean(BytesList[i + 2] & (1 << 2)));
                    first.time.Add(BytesList[i] << 8 | BytesList[i + 1]);
                }
                else { first.time[first.counter] += BytesList[i] << 8 | BytesList[i + 1]; }
                if ((Convert.ToBoolean(BytesList[i + 2] & (1 << 4))) != second.state[first.counter]) {
                    second.counter++;
                    second.state.Add(Convert.ToBoolean(BytesList[i + 2] & (1 << 4)));
                    second.time.Add(BytesList[i] << 8 | BytesList[i + 1]);
                }
                else { second.time[first.counter] += BytesList[i] << 8 | BytesList[i + 1]; }
                if ((Convert.ToBoolean(BytesList[i + 2] & (1 << 7))) != third.state[first.counter]) {
                    third.counter++;
                    third.state.Add(Convert.ToBoolean(BytesList[i + 2] & (1 << 7)));
                    third.time.Add(BytesList[i] << 8 | BytesList[i + 1]);
                }
                else { third.time[first.counter] += BytesList[i] << 8 | BytesList[i + 1]; }
                AllTime += (float)(BytesList[i] << 8 | BytesList[i + 1]);
            }
            SetSignalParams(first);
            SetSignalParams(second);
            SetSignalParams(third);
            Console.ReadKey();
            return 0;
        }
        public static void SetSignalParams(Signals signal) {
            signal.Min = signal.Max = signal.time[0];
            for (int i = 0; i <= signal.counter; i++) {
                if (signal.time[i] < signal.Min) {
                    signal.Min = signal.time[i];
                }
                if (signal.Max < signal.time[i]) {
                    signal.Max = signal.time[i];
                }
                signal.Middle += (float)signal.time[i];
            }
            signal.Middle /= ((float)signal.counter + (float)1);
            signal.Hz = (float)1000 / signal.Middle;
            Console.WriteLine("Минимальное время без изменения состояния - " + signal.Min.ToString() + "ms");
            Console.WriteLine("Максимальное время без изменения состояния - " + signal.Max.ToString() + "ms");
            Console.WriteLine("Среднее время изменения состояний - " + signal.Middle.ToString() + "ms");
            Console.WriteLine("Сигнал обработан, средняя частота сигнала " + signal.Hz.ToString() + "\n");
        }
    }
}