using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;

namespace Pbkdf_Managed
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 1)
            {
                string password = args[0];

                byte[] salt = new byte[16];
                new RNGCryptoServiceProvider().GetBytes(salt);

                Rfc2898DeriveBytes pdb = new Rfc2898DeriveBytes(password, salt, 12000);
                byte[] key = pdb.GetBytes(16);
                byte[] iv = pdb.GetBytes(16);

                Console.WriteLine("Key: " + Convert.ToBase64String(key));
                Console.WriteLine("IV : " + Convert.ToBase64String(iv));
            }
        }
    }
}
