using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace STomorito
{

    /// <summary>
    /// -----|---
    ///    0 |  00
    ///    1 |  01
    ///    2 |  10
    ///    3 |  11
    /// </summary>


    class SFrar : SuperRar
    {
        int N = 256;// szimbólum szám
        kod_pair[] X;
        List<simbol_dig> szotar;
        //double[] p;
        Node root= new Node();
        

        public class Node
        {
            public Node parent = null;
            public Node _0=null,_1=null;
            
        }
        public struct simbol_dig
        {
            public Node myleaf;

            public List<bool> bits;

            public ushort digit;
            public int CompareTo(object obj)
            {
                var other = (simbol_dig)obj;
                return digit.CompareTo(other.digit);
            }
        }
        public struct kod_pair: IComparable
        {
            //public List<bool> bits;
            public byte simbol;
            public double p;

            public int CompareTo(object obj)
            {
                var other = (kod_pair)obj;
                return p.CompareTo(other.p);
            }
        }

        public SFrar(int N_)
        {
            N = N_;
            X = new kod_pair[N];
            //p = new double[N];
            szotar = new List<simbol_dig>();
        }


        public byte[] Encoder(byte[] data)
        {
            foreach(byte b in data)
            {
                ushort idx= (ushort)Convert.ToInt16(b);
                X[idx].p++;
            }
            for (ushort i = 0; i < N; i++)
            {
                X[i].simbol = Convert.ToByte(i);
                X[i].p /= data.Length;
            }



            List<kod_pair> list = new List<kod_pair>(X);
            list.Sort();
            list.Reverse();

            root = new Node();
            Recursive_elosztas(root, list);


            // Építsünk szótárat

            for (int i = 0; i < szotar.Count; i++)
            {
                Node act = szotar[i].myleaf;
                while (act.parent != null)
                {
                    var parent = act.parent;
                    if (parent._0 == act)
                    {
                        szotar[i].bits.Add(false);
                    }else
                    {
                        szotar[i].bits.Add(true);
                    }
                    act = parent;
                }
                
                //reverse
                Console.WriteLine(szotar[i].bits.Count+" "+ szotar[i].digit);

            }
            

            for(uint i=0;i<data.Length;i++)
            {
               
            }


            return data;

        }
        //int ccc = 0;
        void Recursive_elosztas(Node parent,List<kod_pair> list)
        {

           // if (list.Count == 2)
               // Console.WriteLine("asd");



                if (list.Count==1)
            {
                //parent.szimbol = list[0].simbol;
                //Console.WriteLine(++ccc);
                simbol_dig sd;
                sd.myleaf = parent;
                sd.digit = (ushort)Convert.ToInt16(list[0].simbol);
                sd.bits = new List<bool>();
                szotar.Add(sd);
                return;
            }
            double p_all = 0;
            foreach(kod_pair k in list)
            {
                p_all += k.p;
            }

            int idx = 0;
            if (p_all > 0)
            {
                double p_fel = p_all / 2;
                //Console.WriteLine(p_all);
                double p = 0;
                for (int i = 0; i < list.Count; i++)
                {
                    if (p >= p_fel)
                    {
                        idx = i;
                        break;
                    }
                    p += list[i].p;
                }

            }
            else
                return;
                //idx = list.Count / 2;

           /* var _0list = list.GetRange(0, idx);
            var _1list = list.GetRange(idx, list.Count - idx);
           */
            parent._0 = new Node();
            parent._1 = new Node();

            parent._0.parent = parent;
            parent._1.parent = parent;
            //if(_0list.Count==1)

            Recursive_elosztas(parent._0, list.GetRange(0, idx));
            Recursive_elosztas(parent._1, list.GetRange(idx, list.Count - idx));

            


        }






        public byte[] Decoder(byte[] data)
        {
            throw new NotImplementedException();
        }
    }
}
