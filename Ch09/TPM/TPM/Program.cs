using System;
using System.Collections.Generic;
using System.Text;
using System.Management;

namespace TPM
{
    class Program
    {
        static private ManagementObject m_wmiObject = null;

        static Boolean BooleanMethod(String method)
        {
            ManagementBaseObject outParams = m_wmiObject.InvokeMethod(method, null, null);
            return (0 == (UInt32)outParams["ReturnValue"]) ? false : true;
        }

        static void Main(string[] args)
        {
            try
            {
                string tpm = "root\\cimv2\\security\\microsofttpm:Win32_Tpm=@";
                m_wmiObject = new ManagementObject(tpm);
                String version = m_wmiObject.GetPropertyValue("SpecVersion").ToString();
                Boolean fEnabled = BooleanMethod("IsEnabled");
                UInt32 id = (UInt32)m_wmiObject.GetPropertyValue("ManufacturerId");
            }
            catch (ManagementException me)
            {
                Console.WriteLine(me.Message);
            }
        }
    }
}
