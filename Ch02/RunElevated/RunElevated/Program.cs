using System;
using System.Diagnostics;

namespace RunElevated
{
    class Program
    {
        static void Main(string[] args)
        {
            Process p = new Process();
            ProcessStartInfo psi = new ProcessStartInfo(@"cmd.exe");
            psi.UseShellExecute = true;
            psi.Verb = "runas";
            p.StartInfo = psi;
            p.Start();
        }
    }
}
