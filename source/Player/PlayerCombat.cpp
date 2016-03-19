// ******************************************************************************
// Filename:    PlayerCombat.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Revision History:
//   Initial Revision - 27/02/16
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#include "Player.h"
#include "../utils/Random.h"
#include "../utils/Interpolator.h"
#include "../Projectile/ProjectileManager.h"
#include "../Projectile/Projectile.h"
#include "../VoxGame.h"

// Combat
void Player::PressAttack()
{
	if (IsDead())
	{
		return;
	}

	if (IsBow())
	{
		if (m_bowAttackDelay <= 0.0f)
		{
			if (m_bIsChargingAttack == false)
			{
				m_bIsChargingAttack = true;
				m_chargeAmount = 0.0f;

				LoadWeapon(false, "media/gamedata/items/Arrow/ArrowHold.item");

				if (m_bIsIdle)
				{
					m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, false, AnimationSections_FullBody, "BowCharge", 0.2f);
				}
				else
				{
					m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Head_Body, false, AnimationSections_Head_Body, "BowCharge", 0.2f);
					m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Left_Arm_Hand, false, AnimationSections_Left_Arm_Hand, "BowCharge", 0.2f);
					m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "BowCharge", 0.2f);
				}
			}
		}
	}
	else if (IsBoomerang())
	{
		if (CanAttackRight())
		{
			if (m_bCanThrowWeapon)
			{
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, true, AnimationSections_FullBody, "SwordAttack1", 0.01f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "SwordAttack1", 0.01f);

				Interpolator::GetInstance()->AddFloatInterpolation(&m_animationTimer, 0.0f, 0.22f, 0.22f, 0.0f, NULL, _AttackAnimationTimerFinished, this);

				m_bCanAttackRight = false;
				m_bCanThrowWeapon = false;

				// Start weapon trails
				if (m_pVoxelCharacter->GetRightWeapon())
				{
					if (m_pVoxelCharacter->IsRightWeaponLoaded())
					{
						m_pVoxelCharacter->GetRightWeapon()->StartWeaponTrails();
					}
				}
			}
		}
	}
	else if (IsStaff())
	{
		if (CanAttackRight())
		{
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "StaffAttack", 0.01f);
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Left_Arm_Hand, false, AnimationSections_Left_Arm_Hand, "StaffAttack", 0.01f);
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Head_Body, false, AnimationSections_Head_Body, "StaffAttack", 0.01f);

			Interpolator::GetInstance()->AddFloatInterpolation(&m_animationTimer, 0.0f, 0.2f, 0.2f, 0.0f, NULL, _AttackAnimationTimerFinished, this);

			m_bCanAttackRight = false;
		}
	}
	else if (IsWand())
	{
	}
	else if (IsBomb())
	{
	}
	else if (IsConsumable())
	{
	}
	else if (IsDagger())
	{
	}
	else if (IsHammer())
	{
	}
	else if (IsMace())
	{
	}
	else if (IsSickle())
	{
	}
	else if (IsPickaxe())
	{
		if (CanAttackRight())
		{
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, true, AnimationSections_FullBody, "Mine", 0.01f);
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "Mine", 0.01f);

			m_bCanAttackRight = false;
		}
	}
	else if (IsAxe())
	{
	}
	else if (Is2HandedSword())
	{
		if (CanAttackRight())
		{
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, true, AnimationSections_FullBody, "2HandedSwordAttack", 0.01f);
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "2HandedSwordAttack", 0.01f);
			m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Left_Arm_Hand, false, AnimationSections_Left_Arm_Hand, "2HandedSwordAttack", 0.01f);

			m_bCanAttackRight = false;
		}
	}
	else if (IsSword())
	{
		if (CanAttackRight())
		{
			int randomAttack = GetRandomNumber(1, 3);
			if (randomAttack == 1)
			{
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, true, AnimationSections_FullBody, "SwordAttack1", 0.01f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Head_Body, false, AnimationSections_Head_Body, "SwordAttack1", 0.01f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "SwordAttack1", 0.01f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Left_Arm_Hand, false, AnimationSections_Left_Arm_Hand, "SwordAttack1", 0.01f);

				m_bCanInteruptCombatAnim = true;
			}
			else if (randomAttack == 2)
			{
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, true, AnimationSections_FullBody, "SwordAttack2", 0.01f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Head_Body, false, AnimationSections_Head_Body, "SwordAttack2", 0.01f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "SwordAttack2", 0.01f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Left_Arm_Hand, false, AnimationSections_Left_Arm_Hand, "SwordAttack1", 0.01f);

				m_bCanInteruptCombatAnim = true;
			}
			else if (randomAttack == 3)
			{
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, false, AnimationSections_FullBody, "SwordAttack3", 0.01f);

				m_bCanInteruptCombatAnim = false;
			}

			m_bCanAttackRight = false;
		}
	}
	else if (IsBlockPlacing())
	{
	}
	else if (IsItemPlacing())
	{
	}
	else if (IsSceneryPlacing())
	{
	}
	else if (IsSpellHands())
	{
	}
	else if (IsShield())
	{
	}
	else if (IsTorch())
	{
	}
}

void Player::ReleaseAttack()
{
	if (IsDead())
	{
		return;
	}

	if (IsBow())
	{
		if (m_bIsChargingAttack == true)
		{
			UnloadWeapon(false);

			Projectile* pProjectile = m_pProjectileManager->CreateProjectile(m_chargeSpawnPosition, m_chargeSpawnVelocity, 0.0f, "media/gamedata/items/Arrow/Arrow.item", 0.08f);
			pProjectile->SetProjectileType(true, false, false);
			pProjectile->SetOwner(this, NULL, NULL);

			m_bIsChargingAttack = false;
			m_chargeAmount = 0.0f;
			m_bowAttackDelay = 0.125f;

			if (m_bIsIdle)
			{
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, false, AnimationSections_FullBody, "BindPose", 0.2f);
			}
			else
			{
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Head_Body, false, AnimationSections_Head_Body, "BindPose", 0.2f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Left_Arm_Hand, false, AnimationSections_Left_Arm_Hand, "BindPose", 0.2f);
				m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "BindPose", 0.2f);
			}
		}
	}
}

bool Player::CanAttackLeft()
{
	return m_bCanAttackLeft;
}

bool Player::CanAttackRight()
{
	return m_bCanAttackRight;
}

void Player::CheckProjectileDamageRadius(Projectile* pProjectile)
{
	if (m_dead == true)
	{
		return;
	}

	if (pProjectile->CanAttackPlayer() == false && pProjectile->IsReturnToPlayer() == false)
	{
		return;
	}

	vec3 projectileHitboxCenter = GetProjectileHitboxCenter();

	vec3 toProjectile = projectileHitboxCenter - pProjectile->GetCenter();

	bool hitByProjectile = false;
	if (m_eProjectileHitboxType == eProjectileHitboxType_Sphere)
	{
		if (length(toProjectile) < GetRadius() + pProjectile->GetRadius())
		{
			hitByProjectile = true;
		}
	}
	else if (m_eProjectileHitboxType == eProjectileHitboxType_Cube)
	{
		Plane3D planes[6];
		Matrix4x4 rotationMatrix;
		rotationMatrix.SetYRotation(DegToRad(GetRotation()));
		planes[0] = Plane3D(rotationMatrix * vec3(-1.0f, 0.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * vec3(m_projectileHitboxXLength, 0.0f, 0.0f)));
		planes[1] = Plane3D(rotationMatrix * vec3(1.0f, 0.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * vec3(-m_projectileHitboxXLength, 0.0f, 0.0f)));
		planes[2] = Plane3D(rotationMatrix * vec3(0.0f, -1.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * vec3(0.0f, m_projectileHitboxYLength, 0.0f)));
		planes[3] = Plane3D(rotationMatrix * vec3(0.0f, 1.0f, 0.0f), projectileHitboxCenter + (rotationMatrix * vec3(0.0f, -m_projectileHitboxYLength, 0.0f)));
		planes[4] = Plane3D(rotationMatrix * vec3(0.0f, 0.0f, -1.0f), projectileHitboxCenter + (rotationMatrix * vec3(0.0f, 0.0f, m_projectileHitboxZLength)));
		planes[5] = Plane3D(rotationMatrix * vec3(0.0f, 0.0f, 1.0f), projectileHitboxCenter + (rotationMatrix * vec3(0.0f, 0.0f, -m_projectileHitboxZLength)));

		float distance;
		int inside = 0;
		vec3 normal;

		for (int i = 0; i < 6; i++)
		{
			distance = planes[i].GetPointDistance(pProjectile->GetCenter());

			if (distance < -pProjectile->GetRadius())
			{
				// Outside...
			}
			else if (distance < pProjectile->GetRadius())
			{
				// Intersecting..
				inside++;
			}
			else
			{
				// Inside...
				inside++;
			}
		}

		if (inside == 6)
		{
			hitByProjectile = true;
		}
	}

	if (hitByProjectile)
	{
		if (pProjectile->IsReturnToPlayer())
		{
			if (pProjectile->CanCatch())
			{
				pProjectile->PlayerCatch();

				m_bCanThrowWeapon = true;

				if (IsBoomerang())
				{
					m_pVoxelCharacter->SetRenderRightWeapon(true);

					m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, true, AnimationSections_FullBody, "SwordAttack1", 0.01f);
					m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_Right_Arm_Hand, false, AnimationSections_Right_Arm_Hand, "SwordAttack1", 0.01f);

					// Start weapon trails
					if (m_pVoxelCharacter->GetRightWeapon())
					{
						if (m_pVoxelCharacter->IsRightWeaponLoaded())
						{
							m_pVoxelCharacter->GetRightWeapon()->StartWeaponTrails();
						}
					}
				}
			}
		}
		else
		{
			vec3 knockbackDirection = (normalize(pProjectile->GetVelocity())*2.0f) + vec3(0.0f, 1.0f, 0.0f);
			knockbackDirection = normalize(knockbackDirection);
			Colour damageColour = Colour(1.0f, 1.0f, 1.0f);

			float knockbackAmount = 16.0f;
			DoDamage(15.0f, damageColour, knockbackDirection, knockbackAmount, false);

			pProjectile->Explode();
		}
	}
}

void Player::DoDamage(float amount, Colour textColour, vec3 knockbackDirection, float knockbackAmount, bool createParticleHit)
{
	if (m_dead == true)
	{
		return;
	}

	if (m_damageTimer <= 0.0f)
	{
		float healthBefore = m_health;
		float damageDone = healthBefore - m_health;

		m_health -= amount;

		// Figure out if we are dead yet
		if (m_health <= 0.0f)
		{
			m_health = 0.0f;

			// Explode the voxel model
			Explode();
		}

		// Update HUD player data
		// TODO : Player HUD
		//m_pGameWindow->GetHUD()->UpdatePlayerData();

		// Play a hit response animation
		m_pVoxelCharacter->BlendIntoAnimation(AnimationSections_FullBody, false, AnimationSections_FullBody, "HitResponse", 0.01f);

		// Do an animated text effect
		vec3 screenposition = GetCenter() + vec3(GetRandomNumber(-1, 1, 2)*0.25f, 0.0f, GetRandomNumber(-1, 1, 2)*0.25f);
		char damageText[32];
		sprintf(damageText, "%i", (int)amount);
		AnimatedText* lpTestTextEffect = m_pTextEffectsManager->CreateTextEffect(VoxGame::GetInstance()->GetFrontendManager()->GetTextEffectFont(), VoxGame::GetInstance()->GetFrontendManager()->GetTextEffectOutlineFont(), VoxGame::GetInstance()->GetDefaultViewport(), TextDrawMode_3D_Screen, TextEffect_FadeUp, TextDrawStyle_Outline, screenposition, textColour, Colour(0.0f, 0.0f, 0.0f), damageText, 1.0f);
		lpTestTextEffect->SetAutoDelete(true);
		lpTestTextEffect->StartEffect();

		if (createParticleHit && m_health > 0.0f)
		{
			// Do a hit particle effect
			vec3 hitParticlePos = GetCenter() - (normalize(knockbackDirection) * m_radius);
			unsigned int effectId = -1;
			BlockParticleEffect* pBlockParticleEffect = VoxGame::GetInstance()->GetBlockParticleManager()->ImportParticleEffect("media/gamedata/particles/combat_hit.effect", hitParticlePos, &effectId);
			pBlockParticleEffect->PlayEffect();
		}

		// Set face to sad for a short while (until facial hit timer resets);
		m_pVoxelCharacter->PlayFacialExpression("Sad");
		m_hitFacialExpressionTimer = m_hitFacialExpressionTime;
		m_returnToNormalFacialExpressionAfterHit = false;

		m_damageTimer = m_damageTime;
	}

	if (m_dead == true)
	{
		return;
	}

	if (m_knockbackTimer <= 0.0f)
	{
		m_velocity += knockbackDirection * knockbackAmount;

		m_knockbackTimer = m_knockbackTime;
	}
}

void Player::Explode()
{
	if (m_dead == true)
	{
		return;
	}

	m_dead = true;

	m_bIsChargingAttack = false;
	m_chargeAmount = 0.0f;

	// TODO : Player died
	//m_pGameWindow->ReleaseEnemyTarget();
	//m_pGameWindow->GetHUD()->PlayerDied();
	//m_pGameWindow->CloseAllGUIWindows();

	CalculateWorldTransformMatrix();

	// Explode the qubicle binary voxel file
	for (int explodeCounter = 0; explodeCounter < 3; explodeCounter++)
	{
		QubicleBinary* pQubicleModel = NULL;
		int spawnChance = 100;
		if (explodeCounter == 0)
		{
			pQubicleModel = m_pVoxelCharacter->GetQubicleModel();
			spawnChance = 50;
		}
		else if (explodeCounter == 1)
		{
			if (m_pVoxelCharacter->GetRightWeapon() != NULL)
			{
				if (m_pVoxelCharacter->IsRightWeaponLoaded())
				{
					for (int animatedSectionsIndex = 0; animatedSectionsIndex < m_pVoxelCharacter->GetRightWeapon()->GetNumAimatedSections(); animatedSectionsIndex++)
					{
						AnimatedSection* pAnimatedSection = m_pVoxelCharacter->GetRightWeapon()->GetAnimatedSection(animatedSectionsIndex);
						pQubicleModel = pAnimatedSection->m_pVoxelObject->GetQubicleModel();
						spawnChance = 100;
					}
				}
			}
		}
		else if (explodeCounter == 2)
		{
			if (m_pVoxelCharacter->GetLeftWeapon() != NULL)
			{
				if (m_pVoxelCharacter->IsLeftWeaponLoaded())
				{
					for (int animatedSectionsIndex = 0; animatedSectionsIndex < m_pVoxelCharacter->GetLeftWeapon()->GetNumAimatedSections(); animatedSectionsIndex++)
					{
						AnimatedSection* pAnimatedSection = m_pVoxelCharacter->GetLeftWeapon()->GetAnimatedSection(animatedSectionsIndex);
						pQubicleModel = pAnimatedSection->m_pVoxelObject->GetQubicleModel();
						spawnChance = 100;
					}
				}
			}
		}

		if (pQubicleModel != NULL)
		{
			m_pBlockParticleManager->ExplodeQubicleBinary(pQubicleModel, m_pVoxelCharacter->GetCharacterScale(), spawnChance);
		}
	}

	// Unload weapons
	UnloadWeapon(true);
	UnloadWeapon(false);

	// Create tombstone
	char tombstoneFilename[64];
	if (GetRandomNumber(0, 100) > 35)
	{
		sprintf(tombstoneFilename, "media/gamedata/items/Tombstone/tombstone1.item");
	}
	else
	{
		sprintf(tombstoneFilename, "media/gamedata/items/Tombstone/tombstone2.item");
	}
	Item* pTombstone = m_pItemManager->CreateItem(GetCenter(), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), tombstoneFilename, eItem_Tombstone, "Tombstone", false, false, 0.08f);
	pTombstone->SetVelocity(vec3(0.0f, 10.0f, 0.0f));
	pTombstone->SetRotation(vec3(0.0f, GetRandomNumber(0, 360, 1), 0.0f));

	// Create a ghost
	m_createGhost = true;
	m_createGhostTimer = 1.5f;
}

void Player::Respawn()
{
	if (m_dead == false)
	{
		return;
	}

	m_position = m_respawnPosition;

	m_health = m_maxHealth;

	// TODO : Player HUD
	//m_pGameWindow->GetHUD()->UpdatePlayerData();

	// Also go through all the equipped items and equip them
	for (int i = 0; i < EquipSlot_NumSlots; i++)
	{
		InventoryItem* pItem = m_pInventoryManager->GetInventoryItemForEquipSlot((EquipSlot)i);
		if (pItem != NULL)
		{
			EquipItem(pItem);
		}
	}

	m_dead = false;
}

// Projectile hitbox
eProjectileHitboxType Player::GetProjectileHitboxType()
{
	return m_eProjectileHitboxType;
}

float Player::GetProjectileHitboxRadius()
{
	return m_projectileHitboxRadius;
}

float Player::GetProjectileHitboxXLength()
{
	return m_projectileHitboxXLength;
}

float Player::GetProjectileHitboxYLength()
{
	return m_projectileHitboxYLength;
}

float Player::GetProjectileHitboxZLength()
{
	return m_projectileHitboxZLength;
}

vec3 Player::GetProjectileHitboxCenter()
{
	return GetCenter() + m_projectileHitboxCenterOffset;
}

void Player::_AttackAnimationTimerFinished(void *apData)
{
	Player* lpPlayer = (Player*)apData;
	lpPlayer->AttackAnimationTimerFinished();
}

void Player::AttackAnimationTimerFinished()
{
	if (IsBow())
	{
	}
	else if (IsBoomerang())
	{
		vec3 boomerangSpawnPosition = GetCenter() + (m_forward*0.75f) + (GetRightVector()*-0.4f) + (GetUpVector()*0.5f);

		float cameraModification = (m_cameraForward.y*17.5f);
		if (m_cameraForward.y < 0.0f)
		{
			cameraModification = (m_cameraForward.y*5.0f);
		}

		vec3 boomerangTarget = boomerangSpawnPosition + m_forward*15.0f + (vec3(0.0f, 1.0f, 0.0f) * cameraModification);

		float curveTime = length(boomerangTarget - boomerangSpawnPosition) / 15.0f;
		if (curveTime <= 0.4f)
			curveTime = 0.4f;

		Projectile* pProjectile = m_pProjectileManager->CreateProjectile(boomerangSpawnPosition, vec3(0.0f, 0.0f, 0.0f), 0.0f, "media/gamedata/weapons/Boomerang/BoomerangThrown.weapon", 0.05f);
		pProjectile->SetProjectileType(true, false, false);
		pProjectile->SetOwner(this, NULL, NULL);
		pProjectile->SetGravityMultiplier(0.0f);
		pProjectile->SetReturnToPlayer(true);
		pProjectile->SetProjectileCurveParams(m_forward, boomerangTarget, curveTime);
		pProjectile->SetWorldCollisionEnabled(true);

		m_pVoxelCharacter->SetRenderRightWeapon(false);
	}
	else if (IsStaff())
	{
		float powerAmount = 25.0f;
		float cameraMultiplier = 25.0f;

		vec3 spellSpawnPosition = GetCenter() + (m_forward*1.25f) + (GetUpVector()*0.25f);

		if (VoxGame::GetInstance()->GetCameraMode() == CameraMode_FirstPerson)
		{
			cameraMultiplier = 30.0f;
			spellSpawnPosition.y += 0.75f;
		}

		vec3 spellSpawnVelocity = m_forward * powerAmount + vec3(0.0f, 1.0f, 0.0f) * (m_cameraForward.y*cameraMultiplier);

		Projectile* pProjectile = m_pProjectileManager->CreateProjectile(spellSpawnPosition, spellSpawnVelocity, 0.0f, "media/gamedata/items/Fireball/Fireball.item", 0.05f);
		pProjectile->SetProjectileType(true, false, false);
		pProjectile->SetOwner(this, NULL, NULL);
		pProjectile->SetGravityMultiplier(0.0f);
	}
	else if (IsWand())
	{
	}
	else if (IsBomb())
	{
	}
	else if (IsConsumable())
	{
	}
	else if (IsDagger())
	{
	}
	else if (IsHammer())
	{
	}
	else if (IsMace())
	{
	}
	else if (IsSickle())
	{
	}
	else if (IsPickaxe())
	{
		Item* pInteractItem = VoxGame::GetInstance()->GetInteractItem();
		if (pInteractItem != NULL)
		{
			pInteractItem->Interact();
		}
		else
		{
			// TODO : DestroyBlock functionality
			//DestroyBlock();
		}
	}
	else if (IsAxe())
	{
	}
	else if (Is2HandedSword())
	{
	}
	else if (IsSword())
	{
	}
	else if (IsBlockPlacing())
	{
	}
	else if (IsItemPlacing())
	{
	}
	else if (IsSceneryPlacing())
	{
	}
	else if (IsSpellHands())
	{
	}
	else if (IsShield())
	{
	}
	else if (IsTorch())
	{
	}
}
