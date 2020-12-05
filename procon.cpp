#include <bits/stdc++.h>
using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif


using pii = pair<int, int>;
using moves = pair<pii, int>;
const int oo = 1e8;
const int max_depth = 1;
const int MAX = 25;
struct tile
{
    int pt, owner;
    bool agent;
};
moves actions[] = {{{0, 1}, 0}, {{0, 1}, 1}, {{0, -1}, 0}, {{0, -1}, 1}, {{1, 0}, 0}, {{1, 0}, 1}, {{-1, 0}, 0}, {{-1, 0}, 1}, {{1, 1}, 0}, {{1, 1}, 1}, {{-1, -1}, 0}, {{-1, -1}, 1}, {{-1, 1}, 0}, {{-1, 1}, 1}, {{1, -1}, 0}, {{1, -1}, 1}};
tile grid[MAX][MAX];
int grid_area[MAX][MAX];
bool visited[MAX][MAX];
vector<pii> fi, se;
int col, row, na;
int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};
int vector<int> fmoves, smoves;
bool check_inside1(int px, int py)
{
    return 0 <= px and px <= row + 1 and 0 <= py and py <= col + 1;
}
bool check_inside(int px, int py, int x, int y)
{
    return 1 <= px + x and px + x <= row and 1 <= py + y and py + y <= col;
}
bool check_valid_action(int act, int team, int px, int py)
{
    int x = actions[act].first.first;
    int y = actions[act].first.second;
    int mv = actions[act].second;
    if (not check_inside(px, py, x, y))
        return false;
    int nx = px + x;
    int ny = py + y;
    if (grid[nx][ny].agent)
        return false;
    if (mv == 0)
    {
        if (grid[nx][ny].owner == 1 - team)
            return true;
        else
            return false;
    }
    else
    {
        if (grid[nx][ny].owner == 1 - team)
            return false;
        else
            return true;
    }
}

int calc_tile(int owner)
{
    int res = 0;
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            if (grid[i][j].owner == owner and grid[i][j].pt > 0)
            {
                res += grid[i][j].pt;
            }
        }
    }
    return res;
}

int calc_area(int owner)
{
    for (int i = 0; i <= row + 1; i++)
    {
        for (int j = 0; j <= col + 1; j++)
        {
            if (grid[i][j].owner == owner)
            {
                grid_area[i][j] = 1;
            }
            else
            {
                grid_area[i][j] = 0;
            }
            visited[i][j] = false;
        }
    }
    queue<pii> q;
    q.emplace(make_pair(0, 0));
    visited[0][0] = true;
    while (q.size())
    {
        pii cp = q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int cx = cp.first + dx[i];
            int cy = cp.second + dy[i];
            if (check_inside1(cx, cy) and not visited[cx][cy] and grid_area[cx][cy] == 0)
            {
                visited[cx][cy] = true;
                q.emplace(make_pair(cx, cy));
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            if (not visited[i][j] and grid_area[i][j] == 0)
            {
                res += abs(grid[i][j].pt);
            }
        }
    }
    return res;
}
int calc_point(int team)
{
    return calc_tile(team) + calc_area(team);
}

int calc_final()
{
    return calc_point(0) - calc_point(1);
}
bool check_end(vector<int> &state)
{
    bool ok = true;
    for (int i = 0; i < (int)state.size(); i++)
    {
        if (state[i] < 15)
        {
            ok = false;
            break;
        }
    }
    return ok;
}
pair<int, vector<int>> mini_max(int team, vector<pii> &fpos, vector<pii> &spos, int depth)
{
    if (depth == max_depth)
    {
        if (team == 1)
        {
            vector<int> agent_moves;
            int num_agent = (int)spos.size();
            agent_moves.assign((int)spos.size(), 0);
            agent_moves[num_agent - 1] = -1;
            int score = oo;
            vector<int> best_moves;
            //debug(agent_moves);
            while (not check_end(agent_moves))
            {
                int curr = num_agent - 1;
                while (curr >= 0 and agent_moves[curr] == 15)
                {
                    curr -= 1;
                }
                agent_moves[curr] += 1;
                for (int i = curr + 1; i < num_agent; i++)
                {
                    agent_moves[i] = 0;
                }
                //debug(agent_moves);
                bool valid = true;
                set<pii> target;
                for (int i = 0; i < num_agent; i++)
                {
                    valid = valid and check_valid_action(agent_moves[i], team, spos[i].first, spos[i].second);
                    if (not valid)
                        break;
                    int px = spos[i].first;
                    int py = spos[i].second;
                    int nx = px + actions[agent_moves[i]].first.first;
                    int ny = py + actions[agent_moves[i]].first.second;
                    if (target.find(make_pair(nx, ny)) != target.end()) {
                        valid = false;
                        break;
                    } else
                    {
                        target.emplace(make_pair(nx, ny));
                    }
                }
                if (not valid)
                {
                    continue;
                }
                //debug(agent_moves);
                vector<int> old_owner;
                for (int i = 0; i < num_agent; i++)
                {
                    int px = spos[i].first;
                    int py = spos[i].second;
                    int nx = px + actions[agent_moves[i]].first.first;
                    int ny = py + actions[agent_moves[i]].first.second;
                    int mv = actions[agent_moves[i]].second;
                    old_owner.push_back(grid[nx][ny].owner);
                    if (mv)
                    {
                        grid[px][py].agent = false;
                        grid[nx][ny].owner = team;
                        grid[nx][ny].agent = true;
                    }
                    else
                    {
                        grid[nx][ny].owner = -1;
                    }
                }
                int curr_score = calc_final();
                // debug(curr_score, agent_moves);
                if (curr_score < score)
                {
                    score = curr_score;
                    best_moves = agent_moves;
                }
                for (int i = 0; i < num_agent; i++)
                {
                    int px = spos[i].first;
                    int py = spos[i].second;
                    int nx = px + actions[agent_moves[i]].first.first;
                    int ny = py + actions[agent_moves[i]].first.second;
                    int mv = actions[agent_moves[i]].second;
                    if (mv)
                    {
                        grid[px][py].agent = true;
                        grid[nx][ny].agent = false;
                        grid[nx][ny].owner = old_owner[i];
                    } else
                    {
                        grid[nx][ny].owner = old_owner[i];
                    }
                }
            }
            return {score, best_moves};
        }
        else
        {
            vector<int> agent_moves;
            int num_agent = (int) fpos.size();
            agent_moves.assign(num_agent, 0);
            agent_moves[num_agent - 1] = -1;
            //debug(agent_moves, num_agent);
            int score = -oo;
            vector<int> best_moves;
            while (!check_end(agent_moves))
            {
                int curr = num_agent - 1;
                while (curr >= 0 and agent_moves[curr] == 15)
                {
                    //debug(curr);
                    curr -= 1;
                }
                agent_moves[curr] += 1;
                for (int i = curr + 1; i < num_agent; i++)
                {
                    agent_moves[i] = 0;
                }
                //debug(agent_moves);
                bool valid = true;
                set<pii> target;
                for (int i = 0; i < num_agent; i++)
                {
                    valid = valid and check_valid_action(agent_moves[i], team, fpos[i].first, fpos[i].second);
                    if (not valid)
                        break;
                    int px = spos[i].first;
                    int py = spos[i].second;
                    int nx = px + actions[agent_moves[i]].first.first;
                    int ny = py + actions[agent_moves[i]].first.second;
                    if (target.find(make_pair(nx, ny)) != target.end()) {
                        valid = false;
                    } else
                    {
                        target.emplace(make_pair(nx, ny));
                    }
                }
                if (not valid)
                    continue;
                vector<int> old_owner;
                vector<pii> new_pos;
                for (int i = 0; i < num_agent; i++)
                {
                    int px = fpos[i].first;
                    int py = fpos[i].second;
                    int nx = px + actions[agent_moves[i]].first.first;
                    int ny = py + actions[agent_moves[i]].first.second;
                    int mv = actions[agent_moves[i]].second;
                    old_owner.push_back(grid[nx][ny].owner);
                    if (mv)
                    {
                        grid[nx][ny].owner = team;
                        grid[nx][ny].agent = true;
                        grid[px][py].agent = false;
                        new_pos.push_back({nx, ny});
                    } else
                    {
                        grid[nx][ny].owner = -1;
                        new_pos.push_back({px, py});
                    }
                }
                pair<int, vector<int>> result = mini_max(1 - team, new_pos, spos, depth);
                //debug(result.first);
                if (result.first > score)
                {
                    score = result.first;
                    best_moves = agent_moves;
                }
                for (int i = 0; i < num_agent; i++)
                {
                    int px = fpos[i].first;
                    int py = fpos[i].second;
                    int nx = px + actions[agent_moves[i]].first.first;
                    int ny = py + actions[agent_moves[i]].first.second;
                    int mv = actions[agent_moves[i]].second;
                    if (mv)
                    {
                        grid[px][py].agent = true;
                        grid[nx][ny].owner = old_owner[i];
                        grid[nx][ny].agent = false;
                    } else
                    {
                        grid[nx][ny].owner = old_owner[i];
                    }
                }
            }
            return {score, best_moves};
        }
    }
    if (team)
    {
        vector<int> agent_moves;
        int num_agent = (int) spos.size();
        //debug(num_agent);
        agent_moves.assign(num_agent, 0);
        agent_moves[num_agent - 1] = -1;
        int score = oo;
        vector<int> best_moves;
        while (not check_end(agent_moves))
        {
            int curr = num_agent - 1;
            if (curr >= 0 and agent_moves[curr] == 15)
            {
                curr -= 1;
            }
            agent_moves[curr] += 1;
            for (int i = curr + 1; i < num_agent; i++)
            {
                agent_moves[i] = 0;
            }
            bool valid = true;
            set<pii> target;
            for (int i = 0; i < num_agent; i++)
            {
                valid = valid and check_valid_action(agent_moves[i], team, spos[i].first, spos[i].second);
                if (not valid)
                    break;
                int px = spos[i].first;
                int py = spos[i].second;
                int nx = px + actions[agent_moves[i]].first.first;
                int ny = py + actions[agent_moves[i]].first.second;
                if (target.find(make_pair(nx, ny)) != target.end()) {
                    valid = false;
                    break;
                } else
                {
                    target.emplace(make_pair(nx, ny));
                }
            }
            if (not valid)
                continue;
            vector<int> old_owner;
            vector<pii> new_pos;
            for (int i = 0; i < num_agent; i++)
            {
                int px = spos[i].first;
                int py = spos[i].second;
                int nx = px + actions[agent_moves[i]].first.first;
                int ny = py + actions[agent_moves[i]].first.second;
                int mv = actions[agent_moves[i]].second;
                old_owner.push_back(grid[nx][ny].owner);
                if (mv)
                {
                    grid[px][py].agent = false;
                    grid[nx][ny].agent = true;
                    grid[nx][ny].owner = team;
                    new_pos.push_back({nx, ny});
                }
                else
                {
                    grid[nx][ny].owner = -1;
                    new_pos.push_back({px, py});
                }
            }
            pair<int, vector<int>> result = mini_max(1 - team, fpos, new_pos, depth + 1);
            if (result.first < score)
            {
                score = result.first;
                best_moves = agent_moves;
            }
            for (int i = 0; i < num_agent; i++)
            {
                int px = spos[i].first;
                int py = spos[i].second;
                int nx = px + actions[agent_moves[i]].first.first;
                int ny = py + actions[agent_moves[i]].first.second;
                int mv = actions[agent_moves[i]].second;
                if (mv)
                {
                    grid[nx][ny].agent = false;
                    grid[nx][ny].owner = old_owner[i];
                    grid[px][py].agent = true;
                } else
                {
                    grid[nx][ny].owner = old_owner[i];
                }
            }
        }
        return {score, best_moves};
    }
    else
    {
        vector<int> agent_moves;
        int num_agent = (int) fpos.size();
        agent_moves.assign(num_agent, 0);
        agent_moves[num_agent - 1] = -1;
        int score = -oo;
        vector<int> best_moves;
        while (not check_end(agent_moves))
        {
            int curr = num_agent - 1;
            if (curr >= 0 and agent_moves[curr] == 15)
            {
                curr -= 1;
            }
            agent_moves[curr] += 1;
            for (int i = curr + 1; i < num_agent; i++)
            {
                agent_moves[i] = 0;
            }
            bool valid = true;
            set<pii> target;
            for (int i = 0; i < num_agent; i++)
            {
                valid = valid and check_valid_action(agent_moves[i], team, fpos[i].first, fpos[i].second);
                if (not valid)
                    break;
                int px = spos[i].first;
                int py = spos[i].second;
                int nx = px + actions[agent_moves[i]].first.first;
                int ny = py + actions[agent_moves[i]].first.second;
                if (target.find(make_pair(nx, ny)) != target.end()) {
                    valid = false;
                    break;
                } else
                {
                    target.emplace(make_pair(nx, ny));
                }
            }
            if (not valid)
                continue;
            vector<int> old_owner;
            vector<pii> new_pos;
            for (int i = 0; i < num_agent; i++)
            {
                int px = fpos[i].first;
                int py = fpos[i].second;
                int nx = px + actions[agent_moves[i]].first.first;
                int ny = py + actions[agent_moves[i]].first.second;
                int mv = actions[agent_moves[i]].second;
                old_owner.push_back(grid[nx][ny].owner);
                if (mv)
                {
                    grid[px][py].agent = false;
                    grid[nx][ny].agent = true;
                    grid[nx][ny].owner = team;
                    new_pos.push_back({nx, ny});
                }
                else
                {
                    grid[nx][ny].owner = -1;
                    new_pos.push_back({px, py});
                }
            }
            pair<int, vector<int>> result = mini_max(1 - team, new_pos, spos, depth);
            if (result.first > score)
            {
                score = result.first;
                best_moves = agent_moves;
            }
            for (int i = 0; i < num_agent; i++)
            {
                int px = fpos[i].first;
                int py = fpos[i].second;
                int nx = px + actions[agent_moves[i]].first.first;
                int ny = py + actions[agent_moves[i]].first.second;
                int mv = actions[agent_moves[i]].second;
                if (mv)
                {
                    grid[nx][ny].agent = false;
                    grid[nx][ny].owner = old_owner[i];
                    grid[px][py].agent = true;
                } else
                {
                    grid[nx][ny].owner = old_owner[i];
                }
            }
        }
        return {score, best_moves};
    }
}
int main()
{
    cin >> row >> col;
    for (int i = 0; i <= row + 1; i++)
    {
        for (int j = 0; j <= col + 1; j++)
        {
            grid[i][j].owner = -1;
        }
    }
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            cin >> grid[i][j].pt >> grid[i][j].owner;
            grid[i][j].agent = false;
        }
    }
    vector<pii> fpos, spos;
    cin >> na;
    int tx, ty;
    for (int i = 0; i < na; i++)
    {
        cin >> tx >> ty;
        fpos.push_back({tx, ty});
        grid[tx][ty].agent = true;
    }
    for (int i = 0; i < na; i++)
    {
        cin >> tx >> ty;
        spos.push_back({tx, ty});
        grid[tx][ty].agent = true;
    }
    pair<int, vector<int>> cp = mini_max(0, fpos, spos, 1);
    debug(cp.first, cp.second);
    //debug(calc_tile(0), calc_area(0));
    return 0;
}
