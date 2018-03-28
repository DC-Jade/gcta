/*
   GCTA: a tool for Genome-wide Complex Trait Analysis

   New implementation: holds phenotype information in plink format

   Developed by Zhili Zheng<zhilizheng@outlook.com>, 2017

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   A copy of the GNU General Public License is attached along with this program.
   If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GCTA2_PHENO_H
#define GCTA2_PHENO_H
#include <vector>
#include <string>
#include <map>
using std::map;
using std::vector;
using std::string;

struct PhenoMask{
    uint8_t mask;
    uint8_t shift;
    PhenoMask(uint8_t mask, uint8_t shift): mask(mask), shift(shift){};
};

typedef map<int, uint8_t> Mask_t;

class Pheno {
public:
    Pheno();
    PhenoMask get_indi_mask(uint32_t ori_index);
    uint8_t get_mask(uint32_t ori_index);
    uint32_t count_raw();
    static void set_keep(vector<string>& indi_marks, vector<string>& marks, vector<uint32_t>& keeps, bool isKeep);
    static void reinit_rm(vector<uint32_t>& keeps, vector<uint32_t>& rms, int total_sample_number);
    uint32_t count_keep();
    void mask_geno_keep(uint8_t *const geno_1block, int num_blocks);
    vector<string> get_id(int from_index, int to_index);
    uint8_t extract_genobit(uint8_t * const buf, int index_in_keep);
    vector<uint32_t>& get_index_keep();
    void get_pheno(vector<string>& ids, vector<double>& pheno);
    void filter_keep_index(vector<uint32_t>& k_index);
    void getMaskBit(uint64_t *maskp);

    static int registerOption(map<string, vector<string>>& options);
    static void processMain();
    static vector<string> read_sublist(string sublist_file, vector<vector<double>> *phenos = NULL, vector<int> *keep_row = NULL);
    static void addOneFileOption(string key_store, string append_string, string key_name,
                                 map<string, vector<string>> options_in, map<string, string>& options);

private:
    vector<string> fid;
    vector<string> pid;
    vector<string> mark;
    vector<string> fa_id;
    vector<string> mo_id;
    vector<int> sex;
    vector<double> pheno;
    vector<uint32_t> index_keep;
    vector<uint32_t> index_rm;
    vector<int> block8_rm;
    vector<uint8_t> mask_rm;
    int num_ind = 0;
    int num_bytes = 0;
    int num_rm = 0;
    int num_keep = 0;
    Mask_t mask_block;
    Mask_t mask_add_block;

    void read_fam(string fam_file);
    void update_pheno(vector<string>& indi_marks, vector<double>& phenos);
    void update_sex(vector<string>& indi_marks, vector<double>& sex);
    void init_mask_block();
    void init_bmask_block();
    void reinit();
    int block_num;
    vector<uint32_t> keep_block_index;
    vector<uint64_t> mask_items;
    vector<uint64_t> mask_add_items;
 
    static map<string, string> options;
    friend class Geno;

};


#endif //GCTA2_PHENO_H
