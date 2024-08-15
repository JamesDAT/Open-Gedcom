using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpenGedcom.DataStructure
{
    public struct GedID
    {
        private readonly uint value;

        public GedID(uint value)
        {
            this.value = value;
        }

        public static implicit operator uint(GedID id) => id.value;
        public static implicit operator GedID(uint value) => new GedID(value);
    }

    public class GedcomFile
    {
        public enum FileVersion
        {
            VERSION_5_5_5,
            VERSION_5_5_1
        }
    }

    /// <summary>
    /// Represents an individual
    /// </summary>
    public class Individual
    {
        public Individual() { }
        public Individual(GedID id) { this.Id = id; }
        public Individual(string name) { this.Name = name; }
        public Individual(GedID id, string name) { this.Id = id; this.Name = name; }

        public GedID? Id { get; set; } = null;
        public string? Name { get; set; } = null;
    }

    public class Streamable
    {
        public GedID Id { get; set; }
        public string? Name { get; set; }
    }
}
