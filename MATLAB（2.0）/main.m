% 读入数据并判断数据合法性
while 1
    A = input("请输入要填写的数独（格式和输入9x9矩阵一致，为空则填零）：");
    if max(max(A))<=9 && min(min(A))>=0 && length(A)==9 && length(A(:,1))==9
        break;
    else
        disp("输入不规范！请重新输入！");
    end
end

% B存储数独中每一个格子可填写的数据。举例：C(4,7,2)为0表示数独第4行第7列不能填写2，为1表示能填写2
B = zeros(9,9,9);
C = ones(9,9);
for i = 1:9
    B(:,:,i) = C;
end

% 检测输入数独数据的合法性
result = check(A);
if result==1
    disp("无解！");
else
    % 根据现有的数独更新B
    [A, B] = update(A,B);
    % 填写数独，success代表填写结果，小于0表示该数独无解，否则一定能得出解
    [A,success] = fill_shudu(A,B);
    
    if success<0
        disp("无解！");
    else
        disp(A);
    end
end