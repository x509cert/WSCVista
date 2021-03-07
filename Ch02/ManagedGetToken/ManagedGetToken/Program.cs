using System;
using System.Collections.Generic;
using System.Text;
using System.Security;
using System.Security.Principal;

namespace ManagedGetToken
{
    class Program
    {
        static void Main(string[] args)
        {
try
{
    WindowsIdentity id = WindowsIdentity.GetCurrent();
    IntPtr token = id.Token;
}
catch (SecurityException e)
{
    Console.WriteLine(e.Message);
}

        }
    }
}
