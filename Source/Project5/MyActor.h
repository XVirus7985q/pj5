#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class AMyActor : public AActor
{
    GENERATED_BODY()

public:
    // ������
    AMyActor();

protected:
    // ���� ���� �� ȣ��Ǵ� �Լ�
    virtual void BeginPlay() override;

public:
    // �� ������ ȣ��Ǵ� �Լ�
    virtual void Tick(float DeltaTime) override;

private:
    // ���� ��ġ�� �����ϴ� 2D ����
    FVector2D Start;

    // ���� ��ġ�� �����ϴ� 2D ���� (�̵� �Ÿ� ����� ���� �ʿ�)
    FVector2D PreviousPosition;

    // �����ϰ� 0 �Ǵ� 1�� ��ȯ
    int32 Step();

    // �̵� �Լ�
    void Move();

    // �̺�Ʈ �߻� ���� �Լ�
    void TriggerEventWithProbability(float Probability);

    // �̵� �Ÿ� ��� �Լ�
    float CalculateDistance(FVector2D First, FVector2D Second);

    // �̵��� �̺�Ʈ �߻� ���� ����
    float TotalDistance;    // �� �̵� �Ÿ�
    int32 TotalEventCount;  // �� �̺�Ʈ �߻� Ƚ��

    // Move �Լ��� �� ���� ����ǵ��� ���� ����
    bool bHasMoved;
};
