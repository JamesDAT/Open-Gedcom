using System.Diagnostics;
using OpenGedcom;
using OpenGedcom.DataStructure;

namespace TestsSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            GedcomRegistry registry = new();
            Individual indi = new("bob");
            Individual indi2 = new("ross");

            registry.AddIndividual(indi);
            registry.AddIndividual(indi2);

            registry.ReadFileAsync("D:\\github\\Repo\\Open-Gedcom\\Samples\\555SAMPLE.ged");

            //foreach (var individualPair in registry.GetIndividualRange(0, 2))
            //{
            //    Console.WriteLine(individualPair.Value.Name);
            //}

            Console.ReadLine();
        }
    }
}
