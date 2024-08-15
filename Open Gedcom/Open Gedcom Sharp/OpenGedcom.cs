using OpenGedcom.DataStructure;
using System.Diagnostics;

namespace OpenGedcom
{
    public class GedcomRegistry
    {
        private Dictionary<GedID, Individual> _Individuals = new();

        public virtual void ReadFile(string path)
        {
            Parser.Parser parser = new();
            _Individuals = parser.Parse(path);
        }

        public virtual async Task ReadFileAsync(string path)
        {
            Parser.Parser parser = new();
            _Individuals = await parser.ParseAsync(path);
        }

        /// <summary>
        /// Add individual to the registry. The registry will use the individuals ID, if the ID is null, it will assume
        /// the next ID in the registry.
        /// Explicit override will remove the assert for individual ID collisions.
        /// </summary>
        /// <param name="individual"></param>
        /// <param name="explicitOverride"></param>
        public void AddIndividual(Individual individual, bool explicitOverride = false)
        {
            if(individual.Id is null)
            {
                if (_Individuals.Count > 0)
                {
                    individual.Id = _Individuals.Last().Key + 1;
                }
                else
                {
                    individual.Id = 0;
                }
            }
            
            Debug.Assert(!_Individuals.ContainsKey(individual.Id ?? 0) || explicitOverride); // trigger on id collision. explicitOverride removes collision assert
            _Individuals[individual.Id ?? 0] = individual;
        }

        /// <summary>
        /// Get individual with id.
        /// </summary>
        /// <param name="id"></param>
        /// <returns>The individual from the registry. Or Null if no Individual is found</returns>
        /// 
        public Individual? GetIndividual(GedID id)
        {
            if(!_Individuals.ContainsKey(id))
            {
                return null;
            }
            return _Individuals[id];
        }

        /// <summary>
        /// Get individual with name.
        /// </summary>
        /// <param name="name"></param>
        /// <returns>The individual from the registry. Or Null if no Individual is found</returns>
        public Individual? GetIndividual(string name)
        {
            return _Individuals.Values.FirstOrDefault(x => x.Name == name); // return the matching name
        }

        /// <summary>
        /// Get a range of individuals from the registry. Beginning at startId and ending at endId, inclusive.
        /// </summary>
        /// <param name="startId"></param>
        /// <param name="endId"></param>
        /// <returns>IEnumerable of pairs of ID and Individual</returns>
        public IEnumerable<KeyValuePair<GedID, Individual>> GetIndividualRange(GedID startId, GedID endId)
        {
            return _Individuals.Where(kvp => kvp.Key >= startId && kvp.Key <= endId);
        }

        /// <summary>
        /// Remove individual with corresponding ID from the registry.
        /// </summary>
        /// <param name="id"></param>
        public void RemoveIndividual(GedID id)
        {
            _Individuals.Remove(id);
        }

        [Obsolete("This function is potentially unsafe, prefer using the registry api", false)]
        public Dictionary<GedID, Individual> GetInternalData()
        {
            return _Individuals;
        }
    }

    public class GedcomStreamRegistry : GedcomRegistry
    {
        private Dictionary<GedID, Streamable> _CachedStreams = new();

        public override void ReadFile(string file)
        {

        }

        public override async Task ReadFileAsync(string path)
        {
            
        }
    }
}
