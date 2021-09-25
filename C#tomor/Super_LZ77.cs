using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace STomorito
{
    class Super_LZ77 : SuperRar
    {
        //<t,h,x>
        int hk=7, he = 6;
        int N = 2;// szimbólum szám
        int n = 1;//szimbólum hossza

        //privát változók
        
        /*Super_LZ77(int N,int hk_,int he_,)
        {

        }*/


        public byte[] Decoder(byte[] data)
        {
            throw new NotImplementedException();
        }

        public byte[] Encoder(byte[] data)
        {
            throw new NotImplementedException();
        }
    }
}
