using System;
using System.Collections.Generic;
using System.Text;
using System.Management;

namespace AddUrlExemption
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                //const string property = @"HTTPExemptionList";
                const string property = @"URLExemptionList";

                ManagementObject setting = new ManagementObject(
                    @"root\CIMV2\Applications\WindowsParentalControls",
                    "WpcSystemSettings=@",
                    new ObjectGetOptions());

                // get list of current exemptions
                string[] exemptions = (string[])setting[property];
                List<string> lst = new List<string>();
                lst.AddRange(exemptions);

                // add our app to the list
                lst.Add(@"c:\MyCode\myapp.exe");
                exemptions = lst.GetRange(0, lst.Count).ToArray();

                // save the updated exemption list
                setting[property] = exemptions;
                setting.Put();
            }
            catch (ManagementException e)
            {
                // This is a version of Windows Vista that does not have
                // Parental Controls, or you are not an admin.
                System.Console.WriteLine(e.ToString());
            }

        }
    }
}
