using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;

namespace FipsOnly
{
    class Program
    {
        static void Main(string[] args)
        {
            string plainText = "Hello, world!";
            MD5CryptoServiceProvider hash = new MD5CryptoServiceProvider();
            byte[] result = hash.ComputeHash(ASCIIEncoding.UTF8.GetBytes(plainText));
        }
    }
}
