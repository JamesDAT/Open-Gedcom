using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenGedcom.DataStructure;

namespace OpenGedcom.Parser
{
    public class Parser
    {
        public async Task<Dictionary<GedID, Individual>> ParseAsync(string file)
        {
            Dictionary<GedID, Individual> dictionary = new();

            Debug.Assert(File.Exists(file), "Specified file does not exist");

            using (StreamReader streamReader = new StreamReader(file))
            {
                await foreach (var line in ReadAllLinesAsync(streamReader))
                {
                    Console.WriteLine(line);
                }
            }

            return dictionary;
        }

        public Dictionary<GedID, Individual> Parse(string file)
        {
            Dictionary<GedID, Individual> dictionary = new();

            Debug.Assert(File.Exists(file), "Specified file does not exist");

            using (StreamReader streamReader = new(file))
            {
                foreach (string line in ReadAllLines(streamReader))
                {
                    Console.WriteLine(line);
                }
            }
            
            return dictionary;
        }

        private IEnumerable<string> ReadAllLines(StreamReader streamReader)
        {
            while (!streamReader.EndOfStream)
            {
                yield return streamReader.ReadLine() ?? "";
            }
        }

        private async IAsyncEnumerable<string> ReadAllLinesAsync(StreamReader streamReader)
        {
            while (!streamReader.EndOfStream)
            {
                yield return await streamReader.ReadLineAsync() ?? "";
            }
        }
    }

}
