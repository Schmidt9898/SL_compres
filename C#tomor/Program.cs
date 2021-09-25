using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace STomorito
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Tömörítő...");



            

            byte[] file = System.IO.File.ReadAllBytes(@"./files/alice29.txt");

            Console.WriteLine(file.Length);

            //var rar = new Super_LZ77(); 
            //byte[] compressed = rar.Encoder()

            SuperRar rar = new SFrar(256);
            byte[] compressed = rar.Encoder(file);

            Console.WriteLine(file[0].ToString());

            Console.ReadKey();
        }
    }
}
