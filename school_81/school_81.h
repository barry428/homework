#include <iostream>
#include <vector>
#include <cmath>
#include <string>

// 定义游乐项目的数据结构
struct Project {
    std::string name;
    int queueTime;      // 排队时间
    int playTime;       // 游玩时间
    int cost;           // 费用
    double rating;      // 网络评分
    std::pair<int, int> coordinates; // 坐标 (x, y)

    // 计算项目的总时间
    int totalTime() const {
        return queueTime + playTime;
    }
};

// 定义解决方案的数据结构
struct Solution {
    std::vector<Project> route;  // 选择的项目组合
    double score = 0.0;          // 综合得分
    int totalTime = 0;           // 总游玩时间
    int totalCost = 0;           // 总花费
};

// 时间评分函数
int calculateTimeScore(int time) {
    if (time <= 20) return 10;
    else if (time <= 40) return 8;
    else if (time <= 60) return 6;
    else if (time <= 80) return 4;
    else return 2;
}

// 费用评分函数
int calculateCostScore(int cost) {
    if (cost <= 40) return 10;
    else if (cost <= 60) return 8;
    else if (cost <= 80) return 6;
    else return 4;
}

// 网络评分直接使用
double calculateRatingScore(double rating) {
    return rating;
}

// 计算两个项目的距离
double calculateDistance(const Project& a, const Project& b) {
    int dx = a.coordinates.first - b.coordinates.first;
    int dy = a.coordinates.second - b.coordinates.second;
    return sqrt(dx * dx + dy * dy);
}

// 距离评分函数
int calculateDistanceScore(double distance) {
    if (distance <= 100) return 10;
    else if (distance <= 200) return 8;
    else if (distance <= 300) return 6;
    else if (distance <= 400) return 4;
    else return 2;
}

// 综合评分计算
double calculateScore(const std::vector<Project>& projects, bool printDetails = false) {
    double totalScore = 0.0;
    for (size_t i = 0; i < projects.size(); ++i) {
        double ratingScore = 0.4 * calculateRatingScore(projects[i].rating);
        double timeScore = 0.2 * calculateTimeScore(projects[i].totalTime());
        double costScore = 0.2 * calculateCostScore(projects[i].cost);
        double distanceScore = 0.0;

        if (i > 0) {
            double distance = calculateDistance(projects[i - 1], projects[i]);
            distanceScore = 0.2 * calculateDistanceScore(distance);
        }

        totalScore += ratingScore + timeScore + costScore + distanceScore;

        if (printDetails) {
            std::cout << "项目: " << projects[i].name << "\n";
            std::cout << "  网络评分: " << ratingScore << "\n";
            std::cout << "  时间评分: " << timeScore << "\n";
            std::cout << "  费用评分: " << costScore << "\n";
            if (i > 0) {
                std::cout << "  距离评分: " << distanceScore << "\n";
            } else {
                std::cout << "  距离评分: 0 (第一个项目)\n";
            }
        }
    }

    return totalScore;
}

// 回溯法
void backtrack(const std::vector<Project>& projects, int index, std::vector<Project>& currentRoute, Solution& bestSolution,
               int maxTime, int maxCost) {
    int currentTotalTime = 0;
    int currentTotalCost = 0;
    for (const Project& p : currentRoute) {
        currentTotalTime += p.totalTime();
        currentTotalCost += p.cost;
    }

    if (currentTotalTime > maxTime || currentTotalCost > maxCost) {
        return; // 超出约束条件
    }

    double currentScore = calculateScore(currentRoute);

    if (currentScore > bestSolution.score) {
        bestSolution.score = currentScore;
        bestSolution.route = currentRoute;
        bestSolution.totalTime = currentTotalTime;
        bestSolution.totalCost = currentTotalCost;
    }

    for (int i = index; i < projects.size(); ++i) {
        currentRoute.push_back(projects[i]);
        backtrack(projects, i + 1, currentRoute, bestSolution, maxTime, maxCost);
        currentRoute.pop_back();
    }
}

// 主函数
int school_81() {
    // 输出权重信息
    std::cout << "权重信息：" << std::endl;
    std::cout << "网络评分权重: 0.4" << std::endl;
    std::cout << "时间评分权重: 0.2" << std::endl;
    std::cout << "费用评分权重: 0.2" << std::endl;
    std::cout << "距离评分权重: 0.2" << std::endl << std::endl;

    // 初始化项目数据
    std::vector<Project> projects = {
            {"过山车", 80, 10, 85, 8.5, {150, 230}},
            {"海盗船", 20, 15, 50, 7.8, {200, 300}},
            {"漂流", 40, 20, 40, 9.0, {300, 350}},
            {"旋转木马", 10, 5, 30, 7.0, {250, 270}},
            {"高空滑索", 30, 20, 70, 8.2, {100, 180}},
            {"激流勇进", 60, 10, 65, 8.8, {400, 450}},
            {"大摆锤", 90, 15, 100, 9.3, {500, 550}},
            {"碰碰车", 15, 10, 45, 6.8, {350, 380}},
            {"鬼屋", 25, 10, 55, 7.5, {450, 480}},
            {"激光战场", 45, 20, 60, 8.0, {550, 600}}
    };

    // 设置约束条件
    int maxTime = 360;   // 总时间上限 (6小时 = 360分钟)
    int maxCost = 300;   // 总费用上限

    // 初始化回溯法
    Solution bestSolution;
    std::vector<Project> currentRoute;
    backtrack(projects, 0, currentRoute, bestSolution, maxTime, maxCost);

    // 输出最佳路线和评分
    std::cout << "\n最佳游玩路线：" << std::endl;
    for (const Project& p : bestSolution.route) {
        std::cout << p.name << " -> ";
    }
    std::cout << std::endl;
    std::cout << "总评分: " << bestSolution.score << std::endl;
    std::cout << "总时间: " << bestSolution.totalTime << " 分钟" << std::endl;
    std::cout << "总费用: " << bestSolution.totalCost << " 元" << std::endl;

    // 输出每个项目的详细评分
    std::cout << "\n每个项目的详细评分：" << std::endl;
    calculateScore(bestSolution.route, true);

    std::cout << std::endl;

    return 0;
}
