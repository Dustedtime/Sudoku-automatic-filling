% 求解数独（递归函数）
function [A,success] = fill_shudu(A, B)
    while 1
        % 检测循环过程中数独是否填写新数据
        success = 0;
        % 遍历数独，根据B更新数独
        for i = 1:9
            for j = 1:9
                if A(i,j)==0
                    num = 0;
                    count = 0;
                    % 通过B判断该空格能否填写
                    for k = 1:9
                        if B(i,j,k)
                            % 该空格可以填写k
                            num = k;
                            count = count+1;
                        end
                    end
                    % 该空格填写失败（已经没有可供填写的数字，之前的递归存在猜测错误），返回上层递归
                    if count==0
                        success = -1;
                        return;
                    % 该空格当前只能填写num
                    elseif count==1
                        A(i,j) = num;
                        [A,B] = update(A,B);
                        success = 1;
                    end
                end
            end
        end
        % 数独填写完成
        if sum(sum(A==0))==0
            success = 1;
            return;
        end
        % 遍历过程中至少填写了一个新空格，更新B矩阵并重新遍历数独尝试进行填写
        if success>0
            [A,B] = update(A,B);
        % 遍历过程中没有新空格被填写，开始进行猜测
        else
            for i = 1:9
                for j = 1:9
                    if A(i,j)==0
                        % 从1到9进行猜测
                        for k = 1:9
                            if B(i,j,k)==1
                                A(i,j) = k;
                                % 使用临时矩阵存储猜测过程中的数独矩阵以及数独可能填写数据的矩阵，并求解
                                [A_tmp,B_tmp] = update(A,B);
                                [A_tmp,success] = fill_shudu(A_tmp,B_tmp);
                                % 求解失败，该次猜测为假，恢复数独矩阵
                                if success<0
                                    A(i,j) = 0;
                                    B(i,j,k) = 0;
                                % 求解成功，该次猜测为真，更新数独矩阵
                                else
                                    A = A_tmp;
                                    return;
                                end
                            end
                        end
                        % 该空格所有猜测均为假，退回上层递归（只能是上面层数的递归猜测出了问题或者数独无解）
                        A(i,j) = 0;
                        success = -1;
                        return;
                    end
                end
            end
            % 根据推测函数无法运行到此处，保险起见此处加上return
            success = -1;
            return;
        end
    end
end