<?php

declare(strict_types=1);

namespace SmashcastApi\Api;


use GuzzleHttp\Exception\GuzzleException;

class UsersApi extends AbstractApiBase
{
    /**
     * @throws GuzzleException
     */
    public function getUserByAccessToken(string $accessToken): ?string
    {
        $response = $this->apiGet("userfromtoken/$accessToken");
        $userData = json_decode($response->getBody()->getContents(), true);

        return $userData['user_name'] ?? null;
    }

    /**
     * @throws GuzzleException
     */
    public function getUserInfo(string $userId, ?string $accessToken = null): ?array
    {
        $response = $this->apiGet("user/$userId", [], $accessToken);
        $userInfo = json_decode($response->getBody()->getContents(), true);
        return isset($userInfo['user_name']) ? $userInfo : null;
    }
}
