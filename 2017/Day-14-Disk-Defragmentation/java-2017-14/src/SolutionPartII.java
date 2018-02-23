/// http://adventofcode.com/2017/day/14
/// liuyubobobo
/// 2018-02-23

public class SolutionPartII {

    private boolean[][] disk;
    private boolean[][] visited;
    private int d[][] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    public SolutionPartII(){}

    public int region_num(String key){

        disk = new boolean[128][128];
        visited = new boolean[128][128];
        for(int i = 0 ; i < 128 ; i ++)
            for(int j = 0 ; j < 128 ; j ++){
                disk[i][j] = false;
                visited[i][j] = false;
        }

        get_disk(key);

        int res = 0;
        for(int i = 0 ; i < 128 ; i ++)
            for(int j = 0 ; j < 128 ; j ++)
                if(disk[i][j] && !visited[i][j]){
                    dfs(i, j);
                    res ++;
                }
        return res;
    }

    private void dfs(int x, int y){

        visited[x][y] = true;
        for(int i = 0 ; i < 4 ; i ++){
            int newX = x + d[i][0];
            int newY = y + d[i][1];
            if(inArea(newX, newY) && disk[newX][newY] && !visited[newX][newY])
                dfs(newX, newY);
        }
    }

    private boolean inArea(int x, int y){
        return x >= 0 && x < 128 && y >= 0 && y < 128;
    }

    private void get_disk(String key){

        for(int i = 0 ; i < 128 ; i ++){
            int[] hashcode = hash(key + "-" + Integer.toString(i));
            assert hashcode.length == 16;
            for(int j = 0; j < 16; j ++){
                int num = hashcode[j];
                for(int k = 0; k < 8 ; k ++){
                    disk[i][8 * j + 7 - k] = ((num&1) != 0 ? true : false);
                    num >>= 1;
                    visited[i][8 * j + 7 - k] = false;
                }
                assert num == 0;
            }
        }
    }

    private int[] hash(String line){

        int[] lengths = get_lengths(line);

        int[] numbers = new int[256];
        for(int i = 0 ; i < 256 ; i ++)
            numbers[i] = i;

        int cur = 0, skip = 0;
        for(int round = 0 ; round < 64 ; round ++)
            for(int length: lengths){

                int[] tvec = new int[length];
                for(int i = 0; i < length; i ++)
                    tvec[i] = numbers[(cur + i) % 256];

                for(int i = 0 ; i < length/2 ; i ++){
                    int t = tvec[i];
                    tvec[i] = tvec[length - 1 - i];
                    tvec[length - 1 - i] = t;
                }

                for(int i = 0; i < length; i ++)
                    numbers[(cur + i) % 256] = tvec[i];

                cur = (cur + length + skip) % 256;
                skip = (skip + 1) % 256;
            }

        int[] dense_hash = new int[16];
        for(int i = 0 ; i < 16 ; i ++){
            int res = numbers[i*16];
            for(int j = 1 ; j < 16 ; j ++)
                res ^= numbers[i*16+j];
            dense_hash[i] = res;
        }

        return dense_hash;
    }

    private int[] get_lengths(String line){

        int[] lengths = new int[line.length() + 5];
        for(int i = 0 ; i < line.length() ; i ++)
            lengths[i] = (int)(line.charAt(i));

        int[] others = {17, 31, 73, 47, 23};
        for(int i = 0 ; i < 5 ; i ++)
            lengths[line.length() + i] = others[i];

        return lengths;
    }

    public static void main(String[] args) {

        System.out.println((new SolutionPartII().region_num("flqrgnkx")));
        System.out.println((new SolutionPartII().region_num("stpzcrnm")));
    }
}
