using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace STomorito
{
    interface SuperRar
    {
        byte[] Encoder(byte[] data);
        byte[] Decoder(byte[] data);

    }
}
