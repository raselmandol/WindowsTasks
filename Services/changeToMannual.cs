using System;
using System.ServiceProcess;

class Program
{
    static void Main()
    {
        string serviceName = "YourServiceName";
        if (ServiceExists(serviceName))
        {
            ServiceController service = new ServiceController(serviceName);

            try
            {
                service.ChangeStartMode(ServiceStartMode.Manual);
                Console.WriteLine("Service set to Manual startup mode.");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error changing service startup mode: {0}", ex.Message);
            }
        }
        else
        {
            Console.WriteLine("Service does not exist.");
        }

        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }
    static bool ServiceExists(string serviceName)
    {
        ServiceController[] services = ServiceController.GetServices();
        foreach (ServiceController service in services)
        {
            if (service.ServiceName.Equals(serviceName, StringComparison.OrdinalIgnoreCase))
            {
                return true;
            }
        }
        return false;
    }
}
